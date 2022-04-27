//
// Created by Parti on 2021/2/4.
//

#include <drogon/drogon.h>
#include <plugins/DataManager.h>
#include <structures/Exceptions.h>
#include <utils/crypto.h>
#include <utils/datetime.h>

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
            config["redis"]["host"].isString() &&
            config["redis"]["port"].isUInt() &&
            config["redis"]["db"].isInt() &&
            config["redis"]["timeout"].isUInt()
    )) {
        LOG_ERROR << R"("Invalid redis config")";
        abort();
    }

    _dataRedis = make_unique<DataRedis>();

    try {
        _dataRedis->connect(
                config["redis"]["host"].asString(),
                config["redis"]["port"].asUInt(),
                config["redis"]["db"].asInt(),
                config["redis"]["timeout"].asUInt()
        );
    } catch (const cpp_redis::redis_error &e) {
        LOG_ERROR << e.what();
        abort();
    }

    _dataMapper = make_unique<orm::Mapper<Mnemosyne::Data >>(app().getDbClient());
    _usersMapper = make_unique<orm::Mapper<Mnemosyne::Users >>(app().getDbClient());

    LOG_INFO << "DataManager loaded.";
}

void DataManager::shutdown() {
    LOG_INFO << "DataManager shutdown.";
}

void DataManager::uploadData(int64_t userId, const RequestJson &requestJson) {
    auto json = requestJson.copy();
    BasicJson tags(json["tags"]);
    json["tags"] = tags.stringify();
    json["uploader"] = userId;
    Mnemosyne::Data data(json);
    _dataMapper->insert(data);
    // TODO: Implement statistics logic
    _dataRedis->uploadData(userId, data.getValueOfId(), tags.ref());
}

Json::Value DataManager::fuzzyData(const RequestJson &requestJson) {
    Json::Value result;
    orm::Criteria criteria(
            Mnemosyne::Data::Cols::_type,
            orm::CompareOperator::EQ,
            requestJson["type"].asString()
    );
    if (requestJson.check("query", JsonValue::String)) {
        criteria = criteria && (orm::Criteria(
                Mnemosyne::Data::Cols::_name,
                orm::CompareOperator::Like,
                "%"s.append(requestJson["query"].asString()).append("%")
        ) || orm::Criteria(
                Mnemosyne::Data::Cols::_tags,
                orm::CompareOperator::Like,
                "%"s.append(requestJson["query"].asString()).append("%")
        ) || orm::Criteria(
                Mnemosyne::Data::Cols::_extra,
                orm::CompareOperator::Like,
                "%"s.append(requestJson["query"].asString()).append("%")
        ));
    }
    for (const auto &data: _dataMapper->findBy(criteria)) {
        result.append(data.toJson());
    }
    return result;
}

Json::Value DataManager::searchData(const RequestJson &requestJson) {
    Json::Value result;
    orm::Criteria criteria(
            Mnemosyne::Data::Cols::_type,
            orm::CompareOperator::EQ,
            requestJson["type"].asString()
    );
    if (requestJson.check("name", JsonValue::String)) {
        criteria = criteria && orm::Criteria(
                Mnemosyne::Data::Cols::_name,
                orm::CompareOperator::Like,
                "%"s.append(requestJson["name"].asString()).append("%")
        );
    }
    if (requestJson.check("tags", JsonValue::Array)) {
        for (const auto &tag: requestJson["tags"]) {
            criteria = criteria && orm::Criteria(
                    Mnemosyne::Data::Cols::_tags,
                    orm::CompareOperator::Like,
                    "%"s.append(tag.asString()).append("%")
            );
        }
    }
    if (requestJson.check("extra", JsonValue::String)) {
        criteria = criteria && orm::Criteria(
                Mnemosyne::Data::Cols::_extra,
                orm::CompareOperator::Like,
                "%"s.append(requestJson["extra"].asString()).append("%")
        );
    }
    for (const auto &data: _dataMapper->findBy(criteria)) {
        result.append(data.toJson());
    }
    return result;
}

void DataManager::modifyData(int64_t userId, const RequestJson &requestJson) {
    auto data = _dataMapper->findByPrimaryKey(requestJson["id"].asInt64());
    if (data.getValueOfUploader() != userId) {
        throw ResponseException(
                i18n("noPermission"),
                ResultCode::noPermission,
                k403Forbidden
        );
    }
    data.updateByJson(requestJson.copy());
}

void DataManager::deleteData(int64_t userId, const RequestJson &requestJson) {
    const auto dataId = requestJson["id"].asInt64();
    auto data = _dataMapper->findByPrimaryKey(dataId);
    if (data.getValueOfUploader() != userId) {
        throw ResponseException(
                i18n("noPermission"),
                ResultCode::noPermission,
                k403Forbidden
        );
    }
    _dataMapper->deleteByPrimaryKey(dataId);
    _dataRedis->deleteData(userId, dataId, BasicJson(data.getValueOfTags()).ref());
}
