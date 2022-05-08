//
// Created by Parti on 2021/2/4.
//

#include <drogon/drogon.h>
#include <plugins/UserManager.h>
#include <structures/ExceptionHandlers.h>
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

void UserManager::initAndStart(const Json::Value &config) {
    if (!(
            config["tokenBucket"]["ip"]["interval"].isUInt64() &&
            config["tokenBucket"]["ip"]["maxCount"].isUInt64() &&
            config["tokenBucket"]["email"]["interval"].isUInt64() &&
            config["tokenBucket"]["email"]["maxCount"].isUInt64() &&
            config["tokenBucket"]["phone"]["interval"].isUInt64() &&
            config["tokenBucket"]["phone"]["maxCount"].isUInt64()
    )) {
        LOG_ERROR << R"(Invalid tokenBucket config)";
        abort();
    }
    _ipInterval = chrono::seconds(config["tokenBucket"]["ip"]["interval"].asUInt64());
    _ipMaxCount = config["tokenBucket"]["ip"]["maxCount"].asUInt64();
    _emailInterval = chrono::seconds(config["tokenBucket"]["email"]["interval"].asUInt64());
    _emailMaxCount = config["tokenBucket"]["email"]["maxCount"].asUInt64();
    _phoneInterval = chrono::seconds(config["tokenBucket"]["phone"]["interval"].asUInt64());
    _phoneMaxCount = config["tokenBucket"]["phone"]["maxCount"].asUInt64();

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
            config["redis"]["db"].isInt() &&
            config["redis"]["timeout"].isUInt() &&
            config["redis"]["expirations"]["refresh"].isInt() &&
            config["redis"]["expirations"]["access"].isInt() &&
            config["redis"]["expirations"]["email"].isInt() &&
            config["redis"]["expirations"]["phone"].isInt()
    )) {
        LOG_ERROR << R"("Invalid redis config")";
        abort();
    }

    _userRedis = make_unique<UserRedis>(move(UserRedis(
            {
                    chrono::minutes(config["redis"]["expirations"]["refresh"].asInt64()),
                    chrono::minutes(config["redis"]["expirations"]["access"].asInt64()),
                    chrono::minutes(config["redis"]["expirations"]["email"].asInt64()),
                    chrono::minutes(config["redis"]["expirations"]["phone"].asInt64())
            }
    )));

    try {
        _userRedis->connect(
                config["redis"]["host"].asString(),
                config["redis"]["port"].asUInt(),
                config["redis"]["db"].asInt(),
                config["redis"]["timeout"].asUInt()
        );
    } catch (const cpp_redis::redis_error &e) {
        LOG_ERROR << e.what();
        abort();
    }

    _usersMapper = make_unique <orm::Mapper<Mnemosyne::Users>> (app().getDbClient());

    LOG_INFO << "UserManager loaded.";
}

void UserManager::shutdown() {
    _userRedis->disconnect();
    LOG_INFO << "UserManager shutdown.";
}

int64_t UserManager::getUserId(const string &accessToken) {
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

RedisToken UserManager::refresh(const string &refreshToken) {
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

void UserManager::verifyEmail(const string &email) {
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

void UserManager::verifyPhone(const string &phone) {
    auto code = data::randomString(8);
    _userRedis->setPhoneCode(phone, code);
    throw ResponseException(
            i18n("notImplemented"),
            ResultCode::internalError,
            k501NotImplemented
    );
}

tuple<RedisToken, bool> UserManager::loginEmailCode(
        const string &email,
        const string &code
) {
    _checkEmailCode(email, code);

    Mnemosyne::Users user;
    if (_usersMapper->count(orm::Criteria(
            Mnemosyne::Users::Cols::_email,
            orm::CompareOperator::EQ,
            email
    )) == 0) {
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
            user.getPassword() == nullptr
    };
}

tuple<RedisToken, bool> UserManager::loginPhoneCode(
        const string &phone,
        const string &code
) {
    _checkPhoneCode(phone, code);

    Mnemosyne::Users user;
    if (_usersMapper->count(orm::Criteria(
            Mnemosyne::Users::Cols::_phone,
            orm::CompareOperator::EQ,
            phone
    )) == 0) {
        user.setPhone(phone);
        _usersMapper->insert(user);
    } else {
        user = _usersMapper->findOne(orm::Criteria(
                Mnemosyne::Users::Cols::_phone,
                orm::CompareOperator::EQ,
                phone
        ));
    }

    return {
            _userRedis->generateTokens(to_string(user.getValueOfId())),
            user.getPassword() == nullptr
    };
}

RedisToken UserManager::loginEmailPassword(
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

RedisToken UserManager::loginPhonePassword(const string &phone, const string &password) {
    try {
        auto user = _usersMapper->findOne(orm::Criteria(
                Mnemosyne::Users::Cols::_phone,
                orm::CompareOperator::EQ,
                phone
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

void UserManager::resetEmail(
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

void UserManager::resetPhone(
        const string &phone,
        const string &code,
        const string &newPassword
) {
    _checkPhoneCode(phone, code);

    try {
        auto user = _usersMapper->findOne(orm::Criteria(
                Mnemosyne::Users::Cols::_phone,
                orm::CompareOperator::EQ,
                phone
        ));
        user.setPassword(newPassword);
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

void UserManager::migrateEmail(
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

void UserManager::migratePhone(
        const string &accessToken,
        const string &newPhone,
        const string &code
) {
    _checkPhoneCode(newPhone, code);

    try {
        auto user = _usersMapper->findOne(orm::Criteria(
                Mnemosyne::Users::Cols::_id,
                orm::CompareOperator::EQ,
                _userRedis->getIdByAccessToken(accessToken)
        ));
        if (user.getValueOfPhone() == newPhone) {
            return;
        }
        if (_usersMapper->count(orm::Criteria(
                Mnemosyne::Users::Cols::_phone,
                orm::CompareOperator::EQ,
                newPhone
        ))) {
            throw ResponseException(
                    i18n("emailExists"),
                    ResultCode::conflict,
                    k409Conflict
            );
        }
        user.setPhone(newPhone);
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

void UserManager::deactivateEmail(const string &accessToken, const string &code) {
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

void UserManager::deactivatePhone(const string &accessToken, const string &code) {
    try {
        auto user = _usersMapper->findOne(orm::Criteria(
                Mnemosyne::Users::Cols::_id,
                orm::CompareOperator::EQ,
                _userRedis->getIdByAccessToken(accessToken)
        ));
        _checkPhoneCode(user.getValueOfPhone(), code);

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

Json::Value UserManager::getUserInfo(const string &accessToken, int64_t userId) {
    int64_t targetId = userId;
    NO_EXCEPTION(
            targetId = _userRedis->getIdByAccessToken(accessToken);
    )
    try {
        auto user = _usersMapper->findOne(orm::Criteria(
                Mnemosyne::Users::Cols::_id,
                orm::CompareOperator::EQ,
                targetId
        )).toJson();
        user.removeMember("password");
        user.removeMember("avatar");
        if (userId > 0) {
            user.removeMember("email");
            user.removeMember("phone");
        }
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

void UserManager::updateUserInfo(const string &accessToken, RequestJson request) {
    try {
        auto user = _usersMapper->findOne(orm::Criteria(
                Mnemosyne::Users::Cols::_id,
                orm::CompareOperator::EQ,
                getUserId(accessToken)
        ));
        if (user.getValueOfPassword().empty()) {
            if (!request.check("password", JsonValue::String)) {
                throw ResponseException(
                        i18n("noPassword"),
                        ResultCode::nullValue,
                        k403Forbidden
                );
            }
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

string UserManager::getAvatar(const string &accessToken, int64_t userId) {
    int64_t targetId = userId;
    NO_EXCEPTION(
            targetId = _userRedis->getIdByAccessToken(accessToken);
    )
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

Json::Value UserManager::getFollows(const string &accessToken, int64_t userId) {
    int64_t targetId = userId;
    NO_EXCEPTION(
            targetId = _userRedis->getIdByAccessToken(accessToken);
    )
    try {
        return _userRedis->getFollows(to_string(targetId));
    } catch (const redis_exception::KeyNotFound &e) {
        LOG_DEBUG << "Key not found:" << e.what();
        throw ResponseException(
                i18n("userNotFound"),
                ResultCode::notFound,
                k404NotFound
        );
    }
}

bool UserManager::follow(const string &accessToken, int64_t followId) {
    return _userRedis->follow(
            to_string(getUserId(accessToken)),
            to_string(followId)
    );
}

Json::Value UserManager::getStarred(const string &accessToken, int64_t userId) {
    int64_t targetId = userId;
    NO_EXCEPTION(
            targetId = _userRedis->getIdByAccessToken(accessToken);
    )
    try {
        return _userRedis->getStarred(to_string(targetId));
    } catch (const redis_exception::KeyNotFound &e) {
        LOG_DEBUG << "Key not found:" << e.what();
        throw ResponseException(
                i18n("userNotFound"),
                ResultCode::notFound,
                k404NotFound
        );
    }
}

void UserManager::dataStar(int64_t userId, int64_t dataId) const {
    _userRedis->dataStar(to_string(userId), to_string(dataId));
}

bool UserManager::ipLimit(const string &ip) const {
    return _userRedis->tokenBucket(
            "ip:" + ip,
            _ipInterval,
            _ipMaxCount
    );
}

bool UserManager::emailLimit(const string &email) const {
    return _userRedis->tokenBucket(
            "email:" + email,
            _emailInterval,
            _emailMaxCount
    );
}

bool UserManager::phoneLimit(const string &phone) const {
    return _userRedis->tokenBucket(
            "phone:" + phone,
            _phoneInterval,
            _phoneMaxCount
    );
}

void UserManager::_checkEmailCode(const string &email, const string &code) {
    try {
        if (!_userRedis->checkEmailCode(email, code)) {
            throw ResponseException(
                    i18n("invalidCode"),
                    ResultCode::notAcceptable,
                    k403Forbidden
            );
        }
        _userRedis->deleteEmailCode(email);
    } catch (const redis_exception::KeyNotFound &e) {
        LOG_DEBUG << "Key not found: " << e.what();
        throw ResponseException(
                i18n("invalidEmail"),
                ResultCode::notFound,
                k404NotFound
        );
    }
}

void UserManager::_checkPhoneCode(const string &phone, const string &code) {
    try {
        if (!_userRedis->checkPhoneCode(phone, code)) {
            throw ResponseException(
                    i18n("invalidCode"),
                    ResultCode::notAcceptable,
                    k403Forbidden
            );
        }
        _userRedis->deletePhoneCode(phone);
    } catch (const redis_exception::KeyNotFound &e) {
        LOG_DEBUG << "Key not found: " << e.what();
        throw ResponseException(
                i18n("invalidEmail"),
                ResultCode::notFound,
                k404NotFound
        );
    }
}
