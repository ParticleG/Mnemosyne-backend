//
// Created by Parti on 2021/2/4.
//

#pragma once

#include <drogon/plugins/Plugin.h>
#include <helpers/EmailHelper.h>
#include <helpers/I18nHelper.h>
#include <helpers/RequestJson.h>
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

        void dataUpload(int64_t userId, const helpers::RequestJson &requestJson);

        Json::Value dataFuzzy(const helpers::RequestJson &requestJson);

        Json::Value dataSearch(const helpers::RequestJson &requestJson);

        bool dataStar(int64_t userId, int64_t dataId);

        void dataModify(int64_t userId, const helpers::RequestJson &requestJson);

        void dataDelete(int64_t userId, int64_t dataId);

    private:
        std::unique_ptr<mnemosyne::structures::DataRedis> _dataRedis;
        std::unique_ptr<drogon::orm::Mapper<drogon_model::Mnemosyne::Data>> _dataMapper;
    };
}

