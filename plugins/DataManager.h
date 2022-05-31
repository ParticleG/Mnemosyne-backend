//
// Created by Parti on 2021/2/4.
//

#pragma once

#include <drogon/plugins/Plugin.h>
#include <helpers/EmailHelper.h>
#include <helpers/I18nHelper.h>
#include <helpers/RequestJson.h>
#include <models/Collection.h>
#include <models/Data.h>
#include <structures/DataRedis.h>
#include <types/DataType.h>

namespace mnemosyne::plugins {
    class DataManager :
            public drogon::Plugin<DataManager>,
            public helpers::I18nHelper<DataManager> {
    public:
        static constexpr char projectName[] = CMAKE_PROJECT_NAME;

    public:
        void initAndStart(const Json::Value &config) override;

        void shutdown() override;

        Json::Value dataPost(const helpers::RequestJson &requestJson);

        Json::Value dataUpload(const helpers::RequestJson &requestJson, const drogon::HttpFile &file);

        Json::Value dataFuzzy(const helpers::RequestJson &requestJson);

        Json::Value dataSearch(const helpers::RequestJson &requestJson);

        Json::Value dataInfo(int64_t dataId);

        void dataModify(const helpers::RequestJson &requestJson);

        void dataDelete(int64_t dataId);

        Json::Value collectionCreate(const helpers::RequestJson &requestJson);

        Json::Value collectionFuzzy(const helpers::RequestJson &requestJson);

        Json::Value collectionSearch(const helpers::RequestJson &requestJson);

        Json::Value collectionInfo(int64_t dataId);

        void collectionModify(const helpers::RequestJson &requestJson);

        void collectionDelete(int64_t collectionId);

    private:
        std::unique_ptr<mnemosyne::structures::DataRedis> _dataRedis;
        std::unique_ptr<drogon::orm::Mapper<drogon_model::Mnemosyne::Collection>> _collectionMapper;
        std::unique_ptr<drogon::orm::Mapper<drogon_model::Mnemosyne::Data>> _dataMapper;
    };
}

