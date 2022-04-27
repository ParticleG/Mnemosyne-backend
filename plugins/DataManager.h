//
// Created by Parti on 2021/2/4.
//

#pragma once

#include <drogon/plugins/Plugin.h>
#include <helpers/EmailHelper.h>
#include <helpers/I18nHelper.h>
#include <helpers/RequestJson.h>
#include <models/Data.h>
#include <models/Users.h>
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

        void uploadData(int64_t userId, const helpers::RequestJson &requestJson);

        Json::Value fuzzyData(const helpers::RequestJson &requestJson);

        Json::Value searchData(const helpers::RequestJson &requestJson);

        void modifyData(int64_t userId, const helpers::RequestJson &requestJson);

        void deleteData(int64_t userId, const helpers::RequestJson &requestJson);

    private:
        std::unique_ptr<mnemosyne::structures::DataRedis> _dataRedis;
        std::unique_ptr<drogon::orm::Mapper<drogon_model::Mnemosyne::Data>> _dataMapper;
        std::unique_ptr<drogon::orm::Mapper<drogon_model::Mnemosyne::Users>> _usersMapper;
    };
}

