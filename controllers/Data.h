//
// Created by particleg on 2021/9/24.
//

#pragma once

#include <drogon/HttpController.h>
#include <plugins/DataManager.h>
#include <plugins/UserManager.h>
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
                    Data::upload,
                    "/upload",
                    drogon::Post,
                    "mnemosyne::filters::CheckAccessToken",
                    "mnemosyne::filters::CheckDataType",
                    "mnemosyne::filters::DataUpload",
            );
            METHOD_ADD(
                    Data::fuzzy,
                    "/fuzzy",
                    drogon::Post,
                    "mnemosyne::filters::CheckDataType",
                    "mnemosyne::filters::DataFuzzy",
            );
            METHOD_ADD(
                    Data::search,
                    "/search",
                    drogon::Post,
                    "mnemosyne::filters::CheckDataType",
                    "mnemosyne::filters::DataSearch",
            );
            METHOD_ADD(
                    Data::star,
                    "/star",
                    drogon::Post,
                    "mnemosyne::filters::CheckAccessToken",
                    "mnemosyne::filters::CheckDataId",
            );
            METHOD_ADD(
                    Data::modify,
                    "/modify",
                    drogon::Put,
                    "mnemosyne::filters::CheckAccessToken",
                    "mnemosyne::filters::DataModify",
            );
            METHOD_ADD(
                    Data::remove,
                    "/remove",
                    drogon::Post,
                    "mnemosyne::filters::CheckAccessToken",
                    "mnemosyne::filters::CheckDataId",
            );
        METHOD_LIST_END

        void upload(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback);

        void fuzzy(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback);

        void search(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback);

        void star(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback);

        void modify(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback);

        void remove(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback);

    private:
        mnemosyne::plugins::DataManager *_dataManager;
        mnemosyne::plugins::UserManager *_userManager;
    };
}