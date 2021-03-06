//
// Created by particleg on 2021/9/24.
//

#include <controllers/Auth.h>
#include <helpers/RequestJson.h>
#include <helpers/ResponseJson.h>
#include <structures/Exceptions.h>

using namespace drogon;
using namespace std;
using namespace mnemosyne::api::v1;
using namespace mnemosyne::helpers;
using namespace mnemosyne::plugins;
using namespace mnemosyne::structures;
using namespace mnemosyne::types;

Auth::Auth() :
        ResponseJsonHandler(
                [](const ResponseException &e, ResponseJson &response) {
                    response.setStatusCode(e.statusCode());
                    // TODO: Check if this causes too much copying
                    response(e.toJson());
                },
                [this](const orm::DrogonDbException &e, ResponseJson &response) {
                    LOG_ERROR << e.base().what();
                    response.setStatusCode(k500InternalServerError);
                    response.setResultCode(ResultCode::databaseError);
                    response.setMessage(i18n("databaseError"));
                },
                [this](const exception &e, ResponseJson &response) {
                    LOG_ERROR << e.what();
                    response.setStatusCode(k500InternalServerError);
                    response.setResultCode(ResultCode::internalError);
                    response.setMessage(i18n("internalError"));
                    response.setReason(e);
                }
        ),
        _userManager(app().getPlugin<UserManager>()) {}

void Auth::check(const HttpRequestPtr &req, function<void(const HttpResponsePtr &)> &&callback) {
    ResponseJson response;
    handleExceptions([&]() {
        response.setData(_userManager->getUserId(
                req->attributes()->get<string>("accessToken")
        ));
    }, response);
    response.httpCallback(callback);
}

void Auth::refresh(const HttpRequestPtr &req, function<void(const HttpResponsePtr &)> &&callback) {
    ResponseJson response;
    handleExceptions([&]() {
        response.setData(move(_userManager->refresh(
                req->attributes()->get<string>("refreshToken")
        ).parse()));
    }, response);
    response.httpCallback(callback);
}

void Auth::verifyEmail(const HttpRequestPtr &req, function<void(const HttpResponsePtr &)> &&callback) {
    ResponseJson response;
    handleExceptions([&]() {
        _userManager->verifyEmail(
                req->attributes()->get<RequestJson>("requestJson")["email"].asString()
        );
    }, response);
    response.httpCallback(callback);
}

void Auth::verifyPhone(const HttpRequestPtr &req, function<void(const HttpResponsePtr &)> &&callback) {
    ResponseJson response;
    handleExceptions([&]() {
        _userManager->verifyPhone(
                req->attributes()->get<RequestJson>("requestJson")["phone"].asString()
        );
    }, response);
    response.httpCallback(callback);
}

void Auth::loginEmail(const HttpRequestPtr &req, function<void(const HttpResponsePtr &)> &&callback) {
    ResponseJson response;
    handleExceptions([&]() {
        auto request = req->attributes()->get<RequestJson>("requestJson");
        if (request.check("code", JsonValue::String)) {
            const auto &[tokens, isNew] = _userManager->loginEmailCode(
                    request["email"].asString(),
                    request["code"].asString()
            );
            if (isNew) { response.setResultCode(ResultCode::continued); }
            response.setData(move(tokens.parse()));
        } else {
            const auto &tokens = _userManager->loginEmailPassword(
                    request["email"].asString(),
                    request["password"].asString()
            );
            response.setData(move(tokens.parse()));
        }
    }, response);
    response.httpCallback(callback);
}

void Auth::loginPhone(const HttpRequestPtr &req, function<void(const HttpResponsePtr &)> &&callback) {
    ResponseJson response;
    handleExceptions([&]() {
        auto request = req->attributes()->get<RequestJson>("requestJson");
        if (request.check("code", JsonValue::String)) {
            const auto &[tokens, isNew] = _userManager->loginPhoneCode(
                    request["phone"].asString(),
                    request["code"].asString()
            );
            if (isNew) { response.setResultCode(ResultCode::continued); }
            response.setData(move(tokens.parse()));
        } else {
            const auto &tokens = _userManager->loginPhonePassword(
                    request["phone"].asString(),
                    request["password"].asString()
            );
            response.setData(move(tokens.parse()));
        }
    }, response);
    response.httpCallback(callback);
}

void Auth::resetEmail(const HttpRequestPtr &req, function<void(const HttpResponsePtr &)> &&callback) {
    ResponseJson response;
    handleExceptions([&]() {
        auto request = req->attributes()->get<RequestJson>("requestJson");
        _userManager->resetEmail(
                request["email"].asString(),
                request["code"].asString(),
                request["newPassword"].asString()
        );
    }, response);
    response.httpCallback(callback);
}

void Auth::resetPhone(const HttpRequestPtr &req, function<void(const HttpResponsePtr &)> &&callback) {
    ResponseJson response;
    handleExceptions([&]() {
        auto request = req->attributes()->get<RequestJson>("requestJson");
        _userManager->resetPhone(
                request["phone"].asString(),
                request["code"].asString(),
                request["newPassword"].asString()
        );
    }, response);
    response.httpCallback(callback);
}

void Auth::migrateEmail(const HttpRequestPtr &req, function<void(const HttpResponsePtr &)> &&callback) {
    ResponseJson response;
    handleExceptions([&]() {
        auto request = req->attributes()->get<RequestJson>("requestJson");
        _userManager->migrateEmail(
                req->attributes()->get<string>("accessToken"),
                request["newEmail"].asString(),
                request["code"].asString()
        );
    }, response);
    response.httpCallback(callback);
}

void Auth::migratePhone(const HttpRequestPtr &req, function<void(const HttpResponsePtr &)> &&callback) {
    ResponseJson response;
    handleExceptions([&]() {
        auto request = req->attributes()->get<RequestJson>("requestJson");
        _userManager->migratePhone(
                req->attributes()->get<string>("accessToken"),
                request["newPhone"].asString(),
                request["code"].asString()
        );
    }, response);
    response.httpCallback(callback);
}

void Auth::deactivateEmail(const HttpRequestPtr &req, function<void(const HttpResponsePtr &)> &&callback) {
    ResponseJson response;
    handleExceptions([&]() {
        auto request = req->attributes()->get<RequestJson>("requestJson");
        _userManager->deactivateEmail(
                req->attributes()->get<string>("accessToken"),
                request["code"].asString()
        );
    }, response);
    response.httpCallback(callback);
}

void Auth::deactivatePhone(const HttpRequestPtr &req, function<void(const HttpResponsePtr &)> &&callback) {
    ResponseJson response;
    handleExceptions([&]() {
        auto request = req->attributes()->get<RequestJson>("requestJson");
        _userManager->deactivatePhone(
                req->attributes()->get<string>("accessToken"),
                request["code"].asString()
        );
    }, response);
    response.httpCallback(callback);
}