//
// Created by Parti on 2021/2/4.
//

#include <drogon/drogon.h>
#include <plugins/DataManager.h>
#include <structures/Exceptions.h>
#include <utils/crypto.h>
#include <utils/data.h>
#include <utils/datetime.h>
#include <utils/io.h>

using namespace drogon;
using namespace drogon_model;
using namespace std;
using namespace mnemosyne::helpers;
using namespace mnemosyne::plugins;
using namespace mnemosyne::structures;
using namespace mnemosyne::types;
using namespace mnemosyne::utils;

void DataManager::initAndStart(const Json::Value &config) {
    if (!(
            config["tokenBucket"]["ip"]["interval"].isUInt64() &&
            config["tokenBucket"]["ip"]["maxCount"].isUInt64() &&
            config["tokenBucket"]["email"]["interval"].isUInt64() &&
            config["tokenBucket"]["email"]["maxCount"].isUInt64()
    )) {
        LOG_ERROR << R"(Invalid tokenBucket config)";
        abort();
    }
    _ipInterval = chrono::seconds(config["tokenBucket"]["ip"]["interval"].asUInt64());
    _ipMaxCount = config["tokenBucket"]["ip"]["maxCount"].asUInt64();
    _emailInterval = chrono::seconds(config["tokenBucket"]["email"]["interval"].asUInt64());
    _emailMaxCount = config["tokenBucket"]["email"]["maxCount"].asUInt64();

    if (!(
            config["smtp"]["server"].isString() &&
            config["smtp"]["account"].isString() &&
            config["smtp"]["password"].isString() &&
            config["smtp"]["senderEmail"].isString() &&
            config["smtp"]["senderName"].isString()
    )) {
        LOG_ERROR << R"(Invalid smtp config)";
        abort();
    }
    _emailHelper = make_unique<EmailHelper>(
            config["smtp"]["server"].asString(),
            config["smtp"]["account"].asString(),
            config["smtp"]["password"].asString(),
            config["smtp"]["senderEmail"].asString(),
            config["smtp"]["senderName"].asString()
    );

    if (!(
            config["redis"]["host"].isString() &&
            config["redis"]["port"].isUInt() &&
            config["redis"]["timeout"].isUInt() &&
            config["redis"]["expirations"]["refresh"].isInt64() &&
            config["redis"]["expirations"]["access"].isInt64() &&
            config["redis"]["expirations"]["email"].isInt64()
    )) {
        LOG_ERROR << R"("Invalid redis config")";
        abort();
    }

    _userRedis = make_unique<UserRedis>(move(UserRedis(
            {
                    chrono::minutes(config["redis"]["expirations"]["refresh"].asInt64()),
                    chrono::minutes(config["redis"]["expirations"]["access"].asInt64()),
                    chrono::minutes(config["redis"]["expirations"]["email"].asInt64())
            }
    )));

    try {
        _userRedis->connect(
                config["redis"]["host"].asString(),
                config["redis"]["port"].asUInt(),
                config["redis"]["timeout"].asUInt()
        );
    } catch (const cpp_redis::redis_error &e) {
        LOG_ERROR << e.what();
        abort();
    }

    _usersMapper = make_unique<orm::Mapper<Mnemosyne::Users>>(app().getDbClient());

    LOG_INFO << "DataManager loaded.";
}

void DataManager::shutdown() {
    _userRedis->disconnect();
    LOG_INFO << "DataManager shutdown.";
}

int64_t DataManager::getUserId(const string &accessToken) {
    try {
        return _userRedis->getIdByAccessToken(accessToken);
    } catch (const redis_exception::KeyNotFound &e) {
        LOG_DEBUG << "Key not found:" << e.what();
        throw ResponseException(
                i18n("invalidAccessToken"),
                ResultCode::notAcceptable,
                k401Unauthorized
        );
    }
}

RedisToken DataManager::refresh(const string &refreshToken) {
    try {
        return move(_userRedis->refresh(refreshToken));
    } catch (const redis_exception::KeyNotFound &e) {
        LOG_DEBUG << "Key not found:" << e.what();
        throw ResponseException(
                i18n("invalidRefreshToken"),
                ResultCode::notAcceptable,
                k401Unauthorized
        );
    }
}

void DataManager::verifyEmail(const string &email) {
    auto code = data::randomString(8);
    _userRedis->setEmailCode(email, code);
    auto mailContent = io::getFileContent("./verifyEmail.html");
    drogon::utils::replaceAll(
            mailContent,
            "{{VERIFY_CODE}}",
            code
    );
    // TODO: Replace with async method
    _emailHelper->smtp(
            email,
            "[Mnemosyne] Verify Code 验证码",
            mailContent
    );
}

tuple<RedisToken, bool> DataManager::loginEmailCode(
        const string &email,
        const string &code
) {
    _checkEmailCode(email, code);

    Mnemosyne::Users user;
    bool isNew = false;
    if (_usersMapper->count(orm::Criteria(
            Mnemosyne::Users::Cols::_email,
            orm::CompareOperator::EQ,
            email
    )) == 0) {
        isNew = true;
        user.setEmail(email);
        _usersMapper->insert(user);
    } else {
        user = _usersMapper->findOne(orm::Criteria(
                Mnemosyne::Users::Cols::_email,
                orm::CompareOperator::EQ,
                email
        ));
    }

    return {
            _userRedis->generateTokens(to_string(user.getValueOfId())),
            isNew
    };
}

RedisToken DataManager::loginEmailPassword(
        const string &email,
        const string &password
) {
    try {
        auto user = _usersMapper->findOne(orm::Criteria(
                Mnemosyne::Users::Cols::_email,
                orm::CompareOperator::EQ,
                email
        ) && orm::Criteria(
                Mnemosyne::Users::Cols::_password,
                orm::CompareOperator::EQ,
                password
        ));

        if (user.getValueOfPassword().empty()) {
            throw ResponseException(
                    i18n("noPassword"),
                    ResultCode::nullValue,
                    k403Forbidden
            );
        }

        return _userRedis->generateTokens(to_string(user.getValueOfId()));
    } catch (const orm::UnexpectedRows &e) {
        LOG_DEBUG << "Unexpected rows: " << e.what();
        throw ResponseException(
                i18n("invalidEmailPass"),
                ResultCode::notAcceptable,
                k403Forbidden
        );
    }
}

void DataManager::resetEmail(
        const string &email,
        const string &code,
        const string &newPassword
) {
    _checkEmailCode(email, code);

    try {
        auto user = _usersMapper->findOne(orm::Criteria(
                Mnemosyne::Users::Cols::_email,
                orm::CompareOperator::EQ,
                email
        ));
        user.setPassword(newPassword);
        if (user.getValueOfIsNew()) {
            user.setIsNew(false);
        }
        _usersMapper->update(user);
    } catch (const orm::UnexpectedRows &e) {
        LOG_DEBUG << "Unexpected rows: " << e.what();
        throw ResponseException(
                i18n("userNotFound"),
                ResultCode::notFound,
                k404NotFound
        );
    }
}

void DataManager::migrateEmail(
        const string &accessToken,
        const string &newEmail,
        const string &code
) {
    _checkEmailCode(newEmail, code);

    try {
        auto user = _usersMapper->findOne(orm::Criteria(
                Mnemosyne::Users::Cols::_id,
                orm::CompareOperator::EQ,
                _userRedis->getIdByAccessToken(accessToken)
        ));
        if (user.getValueOfEmail() == newEmail) {
            return;
        }
        if (_usersMapper->count(orm::Criteria(
                Mnemosyne::Users::Cols::_email,
                orm::CompareOperator::EQ,
                newEmail
        ))) {
            throw ResponseException(
                    i18n("emailExists"),
                    ResultCode::conflict,
                    k409Conflict
            );
        }
        user.setEmail(newEmail);
        _usersMapper->update(user);
    } catch (const redis_exception::KeyNotFound &e) {
        LOG_DEBUG << "Key not found:" << e.what();
        throw ResponseException(
                i18n("invalidAccessToken"),
                ResultCode::notAcceptable,
                k401Unauthorized
        );
    } catch (const orm::UnexpectedRows &e) {
        LOG_DEBUG << "Unexpected rows: " << e.what();
        throw ResponseException(
                i18n("userNotFound"),
                ResultCode::notFound,
                k404NotFound
        );
    }
}

void DataManager::deactivateEmail(
        const string &accessToken,
        const string &code
) {
    try {
        auto user = _usersMapper->findOne(orm::Criteria(
                Mnemosyne::Users::Cols::_id,
                orm::CompareOperator::EQ,
                _userRedis->getIdByAccessToken(accessToken)
        ));
        _checkEmailCode(user.getValueOfEmail(), code);

        _usersMapper->deleteOne(user);
    } catch (const redis_exception::KeyNotFound &e) {
        LOG_DEBUG << "Key not found:" << e.what();
        throw ResponseException(
                i18n("invalidAccessToken"),
                ResultCode::notAcceptable,
                k401Unauthorized
        );
    } catch (const orm::UnexpectedRows &e) {
        LOG_DEBUG << "Unexpected rows: " << e.what();
        throw ResponseException(
                i18n("userNotFound"),
                ResultCode::notFound,
                k404NotFound
        );
    }
}

Json::Value DataManager::getUserInfo(
        const string &accessToken,
        const int64_t &userId
) {
    int64_t targetId;
    try {
        auto tempUserId = _userRedis->getIdByAccessToken(accessToken);
        targetId = userId < 0 ? tempUserId : userId;
    } catch (const redis_exception::KeyNotFound &e) {
        LOG_DEBUG << "Key not found:" << e.what();
        throw ResponseException(
                i18n("invalidAccessToken"),
                ResultCode::notAcceptable,
                k401Unauthorized
        );
    }
    try {
        auto user = _usersMapper->findOne(orm::Criteria(
                Mnemosyne::Users::Cols::_id,
                orm::CompareOperator::EQ,
                targetId
        )).toJson();
        user.removeMember("phone");
        user.removeMember("password");
        user.removeMember("avatar");
        user.removeMember("is_new");
        return user;
    } catch (const orm::UnexpectedRows &e) {
        LOG_DEBUG << "Unexpected rows: " << e.what();
        throw ResponseException(
                i18n("userNotFound"),
                ResultCode::notFound,
                k404NotFound
        );
    }
}

void DataManager::updateUserInfo(
        const string &accessToken,
        RequestJson request
) {
    try {
        auto user = _usersMapper->findOne(orm::Criteria(
                Mnemosyne::Users::Cols::_id,
                orm::CompareOperator::EQ,
                _userRedis->getIdByAccessToken(accessToken)
        ));
        if (user.getValueOfIsNew()) {
            if (!request.check("password", JsonValue::String)) {
                throw ResponseException(
                        i18n("noPassword"),
                        ResultCode::nullValue,
                        k403Forbidden
                );
            }
            user.setIsNew(false);
        } else {
            request.remove("password");
        }
        if (request.check("avatar", JsonValue::String)) {
            user.setAvatarHash(crypto::blake2B(request["avatar"].asString()));
        }
        user.updateByJson(request.ref());
        _usersMapper->update(user);
    } catch (const orm::UnexpectedRows &e) {
        LOG_DEBUG << "Unexpected rows: " << e.what();
        throw ResponseException(
                i18n("userNotFound"),
                ResultCode::notFound,
                k404NotFound
        );
    }
}

string DataManager::getAvatar(
        const string &accessToken,
        const int64_t &userId
) {
    int64_t targetId;
    try {
        auto tempUserId = _userRedis->getIdByAccessToken(accessToken);
        targetId = userId < 0 ? tempUserId : userId;
    } catch (const redis_exception::KeyNotFound &e) {
        LOG_DEBUG << "Key not found:" << e.what();
        throw ResponseException(
                i18n("invalidAccessToken"),
                ResultCode::notAcceptable,
                k401Unauthorized
        );
    }
    try {
        auto user = _usersMapper->findOne(orm::Criteria(
                Mnemosyne::Users::Cols::_id,
                orm::CompareOperator::EQ,
                targetId
        ));
        return user.getValueOfAvatar();
    } catch (const orm::UnexpectedRows &e) {
        LOG_DEBUG << "Unexpected rows: " << e.what();
        throw ResponseException(
                i18n("userNotFound"),
                ResultCode::notFound,
                k404NotFound
        );
    }
}

bool DataManager::ipLimit(const string &ip) const {
    return _userRedis->tokenBucket(
            "ip:" + ip,
            _ipInterval,
            _ipMaxCount
    );
}

bool DataManager::emailLimit(const string &email) const {
    return _userRedis->tokenBucket(
            "email:" + email,
            _emailInterval,
            _emailMaxCount
    );
}

void DataManager::_checkEmailCode(
        const string &email,
        const string &code
) {
    try {
        _userRedis->checkEmailCode(email, code);
        _userRedis->deleteEmailCode(email);
    } catch (const redis_exception::KeyNotFound &e) {
        LOG_DEBUG << "Key not found: " << e.what();
        throw ResponseException(
                i18n("invalidVerifyEmail"),
                ResultCode::notFound,
                k404NotFound
        );
    } catch (const redis_exception::NotEqual &e) {
        LOG_DEBUG << "Value not equal at: " << e.what();
        throw ResponseException(
                i18n("invalidVerifyCode"),
                ResultCode::notAcceptable,
                k403Forbidden
        );
    }
}
