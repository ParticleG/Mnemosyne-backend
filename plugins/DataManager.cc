//
// Created by Parti on 2021/2/4.
//

#include <drogon/drogon.h>
#include <magic_enum.hpp>
#include <plugins/DataManager.h>
#include <structures/Exceptions.h>
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

    _collectionMapper = make_unique<orm::Mapper<Mnemosyne::Collection>>(app().getDbClient());
    _dataMapper = make_unique<orm::Mapper<Mnemosyne::Data>>(app().getDbClient());

    LOG_INFO << "DataManager loaded.";
}

void DataManager::shutdown() {
    LOG_INFO << "DataManager shutdown.";
}

Json::Value DataManager::dataUpload(const RequestJson &requestJson) {
    auto json = requestJson.copy();
    json["tags"] = postgresql::toPgArray(RequestJson{json["tags"]});
    Mnemosyne::Data data(json);
    _dataMapper->insert(data);
    return data.toJson();
}

Json::Value DataManager::dataFuzzy(const RequestJson &requestJson) {
    Json::Value result(Json::arrayValue);
    orm::Criteria criteria(Mnemosyne::Data::Cols::_id, orm::CompareOperator::IsNotNull);
    if (requestJson["type"].asString() != string(enum_name(DataType::Any))) {
        criteria = criteria && orm::Criteria(
                Mnemosyne::Data::Cols::_type,
                orm::CompareOperator::EQ,
                requestJson["type"].asString()
        );
    }

    const auto query = requestJson["query"].asString();

    criteria = criteria && (orm::Criteria(
            postgresql::toCustomSql(
                    R"(to_tsvector('english', {}) @@ plainto_tsquery('english', $?))",
                    Mnemosyne::Data::Cols::_name
            ),
            query
    ) || orm::Criteria(
            postgresql::toCustomSql(
                    R"(to_tsvector('english', {}) @@ plainto_tsquery('english', $?))",
                    Mnemosyne::Data::Cols::_description
            ),
            query
    ) || orm::Criteria(
            postgresql::toCustomSql(
                    R"(to_tsvector('english', text_arr_to_text({})) @@ plainto_tsquery('english', $?))",
                    Mnemosyne::Data::Cols::_tags
            ),
            query
    ) || orm::Criteria(
            postgresql::toCustomSql(
                    R"(to_tsvector('english', {}) @@ plainto_tsquery('english', $?))",
                    Mnemosyne::Data::Cols::_extra
            ),
            query
    ));

    size_t page = 1, perPage = 30;
    if (requestJson["page"].isUInt64()) {
        page = requestJson["page"].asUInt64();
    }
    if (requestJson["perPage"].isUInt64()) {
        perPage = requestJson["perPage"].asUInt64();
    }

    for (const auto &data: _dataMapper->paginate(page, perPage).findBy(criteria)) {
        result.append(data.toJson());
    }

    return result;
}

Json::Value DataManager::dataSearch(const RequestJson &requestJson) {
    Json::Value result;
    orm::Criteria criteria(Mnemosyne::Data::Cols::_id, orm::CompareOperator::IsNotNull);
    if (requestJson["type"].asString() != string(enum_name(DataType::Any))) {
        criteria = criteria && orm::Criteria(
                Mnemosyne::Data::Cols::_type,
                orm::CompareOperator::EQ,
                requestJson["type"].asString()
        );
    }

    if (requestJson.check("name", JsonValue::String)) {
        criteria = criteria && orm::Criteria(
                postgresql::toCustomSql(
                        R"(to_tsvector('english', {}) @@ plainto_tsquery('english', $?))",
                        Mnemosyne::Data::Cols::_name
                ),
                requestJson["name"].asString()
        );
    }
    if (requestJson.check("description", JsonValue::String)) {
        criteria = criteria && orm::Criteria(
                postgresql::toCustomSql(
                        R"(to_tsvector('english', {}) @@ plainto_tsquery('english', $?))",
                        Mnemosyne::Data::Cols::_description
                ),
                requestJson["description"].asString()
        );
    }
    if (requestJson.check("tags", JsonValue::Array)) {
        criteria = criteria && orm::Criteria(
                postgresql::toCustomSql(
                        R"(to_tsvector('english', text_arr_to_text({})) @@ )"
                        R"(plainto_tsquery('english', text_arr_to_text($?)))",
                        Mnemosyne::Data::Cols::_tags
                ),
                postgresql::toPgArray(RequestJson{requestJson["tags"]})
        );
    }
    if (requestJson.check("extra", JsonValue::String)) {
        criteria = criteria && orm::Criteria(
                postgresql::toCustomSql(
                        R"(to_tsvector('english', {}) @@ plainto_tsquery('english', $?))",
                        Mnemosyne::Data::Cols::_extra
                ),
                requestJson["extra"].asString()
        );
    }
    if (requestJson.check("creator", JsonValue::Int64)) {
        criteria = criteria && orm::Criteria(
                Mnemosyne::Data::Cols::_creator,
                orm::CompareOperator::EQ,
                requestJson["creator"].asInt64()
        );
    }

    size_t page = 1, perPage = 30;
    if (requestJson["page"].isUInt64()) {
        page = requestJson["page"].asUInt64();
    }
    if (requestJson["perPage"].isUInt64()) {
        perPage = requestJson["perPage"].asUInt64();
    }

    for (const auto &data: _dataMapper->paginate(page, perPage).findBy(criteria)) {
        result.append(data.toJson());
    }

    return result;
}

void DataManager::dataModify(const RequestJson &requestJson) {
    auto json = requestJson.copy();
    json["tags"] = postgresql::toPgArray(RequestJson{json["tags"]});
    auto data = _dataMapper->findByPrimaryKey(json["id"].asInt64());
    data.updateByJson(json);
    _dataMapper->update(data);
}

void DataManager::dataDelete(int64_t dataId) {
    auto data = _dataMapper->findByPrimaryKey(dataId);
    _dataMapper->deleteByPrimaryKey(dataId);
}

Json::Value DataManager::collectionCreate(const RequestJson &requestJson) {
    auto json = requestJson.copy();
    json["tags"] = postgresql::toPgArray(RequestJson{json["tags"]});
    json["content"] = postgresql::toPgArray(RequestJson{json["content"]});
    Mnemosyne::Collection collection(json);
    _collectionMapper->insert(collection);
    return collection.toJson();
}

Json::Value DataManager::collectionFuzzy(const RequestJson &requestJson) {
    Json::Value result(Json::arrayValue);
    orm::Criteria criteria(Mnemosyne::Collection::Cols::_id, orm::CompareOperator::IsNotNull);

    const auto query = requestJson["query"].asString();

    criteria = criteria && (orm::Criteria(
            postgresql::toCustomSql(
                    R"(to_tsvector('english', {}) @@ plainto_tsquery('english', $?))",
                    Mnemosyne::Collection::Cols::_name
            ),
            query
    ) || orm::Criteria(
            postgresql::toCustomSql(
                    R"(to_tsvector('english', {}) @@ plainto_tsquery('english', $?))",
                    Mnemosyne::Collection::Cols::_description
            ),
            query
    ) || orm::Criteria(
            postgresql::toCustomSql(
                    R"(to_tsvector('english', text_arr_to_text({})) @@ plainto_tsquery('english', $?))",
                    Mnemosyne::Collection::Cols::_tags
            ),
            query
    ) || orm::Criteria(
            postgresql::toCustomSql(
                    R"(to_tsvector('english', {}) @@ plainto_tsquery('english', $?))",
                    Mnemosyne::Collection::Cols::_extra
            ),
            query
    ));

    size_t page = 1, perPage = 30;
    if (requestJson["page"].isUInt64()) {
        page = requestJson["page"].asUInt64();
    }
    if (requestJson["perPage"].isUInt64()) {
        perPage = requestJson["perPage"].asUInt64();
    }

    for (const auto &collection: _collectionMapper->paginate(page, perPage).findBy(criteria)) {
        result.append(collection.toJson());
    }

    return result;
}

Json::Value DataManager::collectionSearch(const RequestJson &requestJson) {
    Json::Value result;
    orm::Criteria criteria(Mnemosyne::Collection::Cols::_id, orm::CompareOperator::IsNotNull);

    if (requestJson.check("name", JsonValue::String)) {
        criteria = criteria && orm::Criteria(
                postgresql::toCustomSql(
                        R"(to_tsvector('english', {}) @@ plainto_tsquery('english', $?))",
                        Mnemosyne::Collection::Cols::_name
                ),
                requestJson["name"].asString()
        );
    }
    if (requestJson.check("description", JsonValue::String)) {
        criteria = criteria && orm::Criteria(
                postgresql::toCustomSql(
                        R"(to_tsvector('english', {}) @@ plainto_tsquery('english', $?))",
                        Mnemosyne::Collection::Cols::_description
                ),
                requestJson["description"].asString()
        );
    }
    if (requestJson.check("tags", JsonValue::Array)) {
        criteria = criteria && orm::Criteria(
                postgresql::toCustomSql(
                        R"(to_tsvector('english', text_arr_to_text({})) @@ )"
                        R"(plainto_tsquery('english', text_arr_to_text($?)))",
                        Mnemosyne::Collection::Cols::_tags
                ),
                postgresql::toPgArray(RequestJson{requestJson["tags"]})
        );
    }
    if (requestJson.check("extra", JsonValue::String)) {
        criteria = criteria && orm::Criteria(
                postgresql::toCustomSql(
                        R"(to_tsvector('english', {}) @@ plainto_tsquery('english', $?))",
                        Mnemosyne::Collection::Cols::_extra
                ),
                requestJson["extra"].asString()
        );
    }
    if (requestJson.check("creator", JsonValue::Int64)) {
        criteria = criteria && orm::Criteria(
                Mnemosyne::Collection::Cols::_creator,
                orm::CompareOperator::EQ,
                requestJson["creator"].asInt64()
        );
    }

    size_t page = 1, perPage = 30;
    if (requestJson["page"].isUInt64()) {
        page = requestJson["page"].asUInt64();
    }
    if (requestJson["perPage"].isUInt64()) {
        perPage = requestJson["perPage"].asUInt64();
    }

    for (const auto &collection: _collectionMapper->paginate(page, perPage).findBy(criteria)) {
        result.append(collection.toJson());
    }

    return result;
}

void DataManager::collectionModify(const RequestJson &requestJson) {
    auto json = requestJson.copy();
    json["tags"] = postgresql::toPgArray(RequestJson{json["tags"]});
    json["content"] = postgresql::toPgArray(RequestJson{json["content"]});
    auto collection = _collectionMapper->findByPrimaryKey(json["id"].asInt64());
    collection.updateByJson(json);
    _collectionMapper->update(collection);
}

void DataManager::collectionDelete(int64_t collectionId) {
    auto collection = _collectionMapper->findByPrimaryKey(collectionId);
    _collectionMapper->deleteByPrimaryKey(collectionId);
}
