//
// Created by particleg on 2021/9/24.
//

#pragma once

#include <drogon/HttpController.h>
#include <plugins/UserManager.h>
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
                    "mnemosyne::filters::CheckUserId"
            );
            METHOD_ADD(
                    User::getFollows,
                    "/follow",
                    drogon::Get,
                    "mnemosyne::filters::CheckAccessToken",
                    "mnemosyne::filters::CheckUserId"
            );
            METHOD_ADD(
                    User::follow,
                    "/follow",
                    drogon::Post,
                    "mnemosyne::filters::CheckAccessToken",
                    "mnemosyne::filters::CheckUserId"
            );
            METHOD_ADD(
                    User::starred,
                    "/starred",
                    drogon::Get,
                    "mnemosyne::filters::CheckAccessToken",
                    "mnemosyne::filters::CheckUserId"
            );
        METHOD_LIST_END

        void getInfo(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback);

        void updateInfo(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback);

        void getAvatar(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback);

        void getFollows(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback);

        void follow(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback);

        void starred(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback);

    private:
        mnemosyne::plugins::UserManager *_userManager;
    };
}