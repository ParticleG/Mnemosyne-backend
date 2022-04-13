//
// Created by particleg on 2021/9/24.
//

#pragma once

#include <drogon/HttpController.h>
#include <plugins/DataManager.h>
#include <structures/ExceptionHandlers.h>

namespace mnemosyne::api::v1 {
    class User :
            public drogon::HttpController<User>,
            public structures::ResponseJsonHandler,
            public helpers::I18nHelper<User> {
    public:
        static constexpr char projectName[] = CMAKE_PROJECT_NAME;

    public:
        User();

        METHOD_LIST_BEGIN
            METHOD_ADD(
                    User::getInfo,
                    "/info",
                    drogon::Get,
                    "mnemosyne::filters::CheckAccessToken",
                    "mnemosyne::filters::CheckUserId"
            );
            METHOD_ADD(
                    User::updateInfo,
                    "/info",
                    drogon::Put,
                    "mnemosyne::filters::CheckAccessToken",
                    "mnemosyne::filters::UserUpdateInfo"
            );
            METHOD_ADD(
                    User::getAvatar,
                    "/avatar",
                    drogon::Get,
                    "mnemosyne::filters::CheckAccessToken",
                    "mnemosyne::filters::CheckUserId");
        METHOD_LIST_END

        void getInfo(
                const drogon::HttpRequestPtr &req,
                std::function<void(const drogon::HttpResponsePtr &)> &&callback
        );

        void updateInfo(
                const drogon::HttpRequestPtr &req,
                std::function<void(const drogon::HttpResponsePtr &)> &&callback
        );

        void getAvatar(
                const drogon::HttpRequestPtr &req,
                std::function<void(const drogon::HttpResponsePtr &)> &&callback
        );

    private:
        mnemosyne::plugins::DataManager *_dataManager;
    };
}