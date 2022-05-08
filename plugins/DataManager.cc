//
// Created by Parti on 2021/2/4.
//

#include <drogon/drogon.h>
#include <magic_enum.hpp>
#include <plugins/DataManager.h>
#include <plugins/UserManager.h>
#include <structures/Exceptions.h>
#include <utils/crypto.h>
#include <utils/datetime.h>
#include <utils/postgresql.h>

using namespace drogon;
using namespace drogon_model;
using namespace magic_enum;
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

    _dataMapper = make_unique<orm::Mapper<Mnemosyne::Data>>(app().getDbClient());

    LOG_INFO << "DataManager loaded.";
}

void DataManager::shutdown() {
    LOG_INFO << "DataManager shutdown.";
}

void DataManager::dataUpload(int64_t userId, const RequestJson &requestJson) {
    auto json = requestJson.copy();
    json["tags"] = postgresql::toPgArray(RequestJson{json["tags"]});
    json["creator"] = userId;
    Mnemosyne::Data data(json);
    _dataMapper->insert(data);
}

Json::Value DataManager::dataFuzzy(const RequestJson &requestJson) {
    Json::Value result;
    std::string sql = R"(select * from data where )"
                      R"((tags @> $1))";
    if (requestJson["type"].asString() != string(enum_name(DataType::Any))) {
        sql += R"( and (type = ')" + requestJson["type"].asString() + R"('))";
    }
    const auto rows = app().getDbClient()->execSqlSync(
            sql,
            "{"s.append(requestJson["query"].asString()).append("}")
    );
    for (const auto &row: rows) {
        Mnemosyne::Data data(row);
        result.append(data.toJson());
    }
    return result;
}

Json::Value DataManager::dataSearch(const RequestJson &requestJson) {
    Json::Value result;
    std::string sql = R"(select * from data where )";

    bool first = true;

    if (requestJson["type"].asString() != string(enum_name(DataType::Any))) {
        first = false;
        sql += R"((type = ')" + requestJson["type"].asString() + R"('))";
    }
    if (requestJson.check("name", JsonValue::String)) {
        if (first) {
            first = false;
        } else {
            sql += " and ";
        }
        sql += R"((name = ')" + requestJson["name"].asString() + R"('))";
    }
    if (requestJson.check("description", JsonValue::String)) {
        if (first) {
            first = false;
        } else {
            sql += " and ";
        }
        sql += R"((description = ')" + requestJson["description"].asString() + R"('))";
    }
    if (requestJson.check("tags", JsonValue::Array)) {
        if (first) {
            first = false;
        } else {
            sql += " and ";
        }
        sql += R"((tags @> )" + postgresql::toPgArray(RequestJson{requestJson["tags"]}) + R"())";
    }
    if (requestJson.check("extra", JsonValue::String)) {
        if (first) {
            first = false;
        } else {
            sql += " and ";
        }
        sql += R"((extra = ')" + requestJson["extra"].asString() + R"('))";
    }
    if (requestJson.check("creator", JsonValue::Int64)) {
        if (!first) {
            sql += " and ";
        }
        sql += R"((creator = )" + to_string(requestJson["creator"].asInt64()) + R"())";
    }
    const auto rows = app().getDbClient()->execSqlSync(sql);
    for (const auto &row: rows) {
        Mnemosyne::Data data(row);
        result.append(data.toJson());
    }
    return result;
}

bool DataManager::dataStar(int64_t userId, int64_t dataId) {
    app().getPlugin<UserManager>()->dataStar(userId, dataId);
    return _dataRedis->dataStar(userId, dataId);
}

void DataManager::dataModify(int64_t userId, const RequestJson &requestJson) {
    auto data = _dataMapper->findByPrimaryKey(requestJson["id"].asInt64());
    if (data.getValueOfCreator() != userId) {
        throw ResponseException(
                i18n("noPermission"),
                ResultCode::noPermission,
                k403Forbidden
        );
    }
    data.updateByJson(requestJson.copy());
}

void DataManager::dataDelete(int64_t userId, int64_t dataId) {
    auto data = _dataMapper->findByPrimaryKey(dataId);
    if (data.getValueOfCreator() != userId) {
        throw ResponseException(
                i18n("noPermission"),
                ResultCode::noPermission,
                k403Forbidden
        );
    }
    _dataMapper->deleteByPrimaryKey(dataId);
}
