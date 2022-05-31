//
// Created by particleg on 2021/9/24.
//

#pragma once

#include <drogon/HttpController.h>
#include <plugins/DataManager.h>
#include <structures/ExceptionHandlers.h>

namespace mnemosyne::api::v1 {
    class Data :
            public drogon::HttpController<Data>,
            public structures::ResponseJsonHandler,
            public helpers::I18nHelper<Data> {
    public:
        static constexpr char projectName[] = CMAKE_PROJECT_NAME;

    public:
        Data();

        METHOD_LIST_BEGIN
            METHOD_ADD(
                    Data::post,
                    "/post",
                    drogon::Post,
                    "mnemosyne::filters::DataPost",
            );
            METHOD_ADD(
                    Data::upload,
                    "/upload",
                    drogon::Post,
                    "mnemosyne::filters::DataUpload",
            );
            METHOD_ADD(
                    Data::fuzzy,
                    "/fuzzy",
                    drogon::Post,
                    "mnemosyne::filters::DataFuzzy",
            );
            METHOD_ADD(
                    Data::search,
                    "/search",
                    drogon::Post,
                    "mnemosyne::filters::DataSearch",
            );
            METHOD_ADD(
                    Data::info,
                    "/info",
                    drogon::Get,
                    "mnemosyne::filters::CheckDataId",
            );
            METHOD_ADD(
                    Data::modify,
                    "/modify",
                    drogon::Put,
                    "mnemosyne::filters::DataModify",
            );
            METHOD_ADD(
                    Data::remove,
                    "/remove",
                    drogon::Post,
                    "mnemosyne::filters::CheckDataId",
            );
        METHOD_LIST_END

        void post(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback);

        void upload(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback);

        void fuzzy(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback);

        void search(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback);

        void info(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback);

        void modify(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback);

        void remove(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback);

    private:
        mnemosyne::plugins::DataManager *_dataManager;
    };
}