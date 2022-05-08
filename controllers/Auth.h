//
// Created by particleg on 2021/9/24.
//

#pragma once

#include <drogon/HttpController.h>
#include <plugins/UserManager.h>
#include <structures/ExceptionHandlers.h>

namespace mnemosyne::api::v1 {
    class Auth :
            public drogon::HttpController<Auth>,
            public structures::ResponseJsonHandler,
            public helpers::I18nHelper<Auth> {
    public:
        static constexpr char projectName[] = CMAKE_PROJECT_NAME;

    public:
        Auth();

        METHOD_LIST_BEGIN
            METHOD_ADD(
                    Auth::check,
                    "/check",
                    drogon::Get,
                    "mnemosyne::filters::CheckAccessToken"
            );
            METHOD_ADD(
                    Auth::refresh,
                    "/refresh",
                    drogon::Get,
                    "mnemosyne::filters::CheckRefreshToken"
            );
            METHOD_ADD(
                    Auth::verifyEmail,
                    "/verify/email",
                    drogon::Post,
                    "mnemosyne::filters::AuthVerifyEmail",
                    "mnemosyne::filters::EmailThreshold",
                    "mnemosyne::filters::IpThreshold"
            );
            METHOD_ADD(
                    Auth::verifyPhone,
                    "/verify/phone",
                    drogon::Post,
                    "mnemosyne::filters::AuthVerifyPhone",
                    "mnemosyne::filters::PhoneThreshold",
                    "mnemosyne::filters::IpThreshold"
            );
            METHOD_ADD(
                    Auth::loginEmail,
                    "/login/email",
                    drogon::Post,
                    "mnemosyne::filters::AuthLoginEmail"
            );
            METHOD_ADD(
                    Auth::loginPhone,
                    "/login/phone",
                    drogon::Post,
                    "mnemosyne::filters::AuthLoginPhone"
            );
            METHOD_ADD(
                    Auth::resetEmail,
                    "/reset/email",
                    drogon::Put,
                    "mnemosyne::filters::AuthResetEmail"
            );
            METHOD_ADD(
                    Auth::resetPhone,
                    "/reset/phone",
                    drogon::Put,
                    "mnemosyne::filters::AuthResetPhone"
            );
            METHOD_ADD(
                    Auth::migrateEmail,
                    "/migrate/email",
                    drogon::Put,
                    "mnemosyne::filters::CheckAccessToken",
                    "mnemosyne::filters::AuthMigrateEmail"
            );
            METHOD_ADD(
                    Auth::migratePhone,
                    "/migrate/phone",
                    drogon::Put,
                    "mnemosyne::filters::CheckAccessToken",
                    "mnemosyne::filters::AuthMigratePhone"
            );
            METHOD_ADD(
                    Auth::deactivateEmail,
                    "/deactivate/email",
                    drogon::Delete,
                    "mnemosyne::filters::CheckAccessToken",
                    "mnemosyne::filters::AuthDeactivateEmail"
            );
            METHOD_ADD(
                    Auth::deactivatePhone,
                    "/deactivate/phone",
                    drogon::Delete,
                    "mnemosyne::filters::CheckAccessToken",
                    "mnemosyne::filters::AuthDeactivatePhone"
            );
        METHOD_LIST_END

        void check(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback);

        void refresh(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback);

        void verifyEmail(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback);

        void verifyPhone(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback);

        void loginEmail(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback);

        void loginPhone(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback);

        void resetEmail(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback);

        void resetPhone(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback);

        void migrateEmail(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback);

        void migratePhone(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback);

        void deactivateEmail(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback);

        void deactivatePhone(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback);

    private:
        plugins::UserManager *_userManager;
    };
}