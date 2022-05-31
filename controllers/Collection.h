//
// Created by particleg on 2021/9/24.
//

#pragma once

#include <drogon/HttpController.h>
#include <plugins/DataManager.h>
#include <structures/ExceptionHandlers.h>

namespace mnemosyne::api::v1 {
    class Collection :
            public drogon::HttpController<Collection>,
            public structures::ResponseJsonHandler,
            public helpers::I18nHelper<Collection> {
    public:
        static constexpr char projectName[] = CMAKE_PROJECT_NAME;

    public:
        Collection();

        METHOD_LIST_BEGIN
            METHOD_ADD(
                    Collection::create,
                    "/create",
                    drogon::Post,
                    "mnemosyne::filters::CollectionCreate",
            );
            METHOD_ADD(
                    Collection::fuzzy,
                    "/fuzzy",
                    drogon::Post,
                    "mnemosyne::filters::CollectionFuzzy",
            );
            METHOD_ADD(
                    Collection::search,
                    "/search",
                    drogon::Post,
                    "mnemosyne::filters::CollectionSearch",
            );
            METHOD_ADD(
                    Collection::info,
                    "/info",
                    drogon::Get,
                    "mnemosyne::filters::CheckCollectionId",
            );
            METHOD_ADD(
                    Collection::modify,
                    "/modify",
                    drogon::Put,
                    "mnemosyne::filters::CollectionModify",
            );
            METHOD_ADD(
                    Collection::remove,
                    "/remove",
                    drogon::Post,
                    "mnemosyne::filters::CheckCollectionId",
            );
        METHOD_LIST_END

        void create(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback);

        void fuzzy(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback);

        void search(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback);

        void info(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback);

        void modify(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback);

        void remove(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback);

    private:
        mnemosyne::plugins::DataManager *_dataManager;
    };
}