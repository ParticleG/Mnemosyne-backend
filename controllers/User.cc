//
// Created by particleg on 2021/9/24.
//

#include <controllers/User.h>
#include <helpers/ResponseJson.h>

using namespace drogon;
using namespace std;
using namespace mnemosyne::api::v1;
using namespace mnemosyne::helpers;
using namespace mnemosyne::plugins;
using namespace mnemosyne::structures;
using namespace mnemosyne::types;

User::User() :
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

void User::getInfo(const HttpRequestPtr &req, function<void(const HttpResponsePtr &)> &&callback) {
    ResponseJson response;
    handleExceptions([&]() {
        response.setData(_userManager->getUserInfo(
                req->attributes()->get<string>("accessToken"),
                req->attributes()->get<int64_t>("userId")
        ));
    }, response);
    response.httpCallback(callback);
}

void User::updateInfo(const HttpRequestPtr &req, function<void(const HttpResponsePtr &)> &&callback) {
    ResponseJson response;
    handleExceptions([&]() {
        _userManager->updateUserInfo(
                req->attributes()->get<string>("accessToken"),
                req->attributes()->get<RequestJson>("requestJson")
        );
    }, response);
    response.httpCallback(callback);
}

void User::getAvatar(const HttpRequestPtr &req, function<void(const HttpResponsePtr &)> &&callback) {
    ResponseJson response;
    handleExceptions([&]() {
        response.setData(_userManager->getAvatar(
                req->attributes()->get<string>("accessToken"),
                req->attributes()->get<int64_t>("userId")
        ));
    }, response);
    response.httpCallback(callback);
}

void User::getFollows(const HttpRequestPtr &req, function<void(const HttpResponsePtr &)> &&callback) {
    ResponseJson response;
    handleExceptions([&]() {
        response.setData(_userManager->getFollows(
                req->attributes()->get<string>("accessToken"),
                req->attributes()->get<int64_t>("userId")
        ));
    }, response);
    response.httpCallback(callback);
}

void User::follow(const HttpRequestPtr &req, function<void(const HttpResponsePtr &)> &&callback) {
    ResponseJson response;
    handleExceptions([&]() {
        response.setData(_userManager->follow(
                req->attributes()->get<string>("accessToken"),
                req->attributes()->get<int64_t>("userId")
        ));
    }, response);
    response.httpCallback(callback);
}

void User::starred(const HttpRequestPtr &req, function<void(const HttpResponsePtr &)> &&callback) {
    ResponseJson response;
    handleExceptions([&]() {
        response.setData(_userManager->getStarred(
                req->attributes()->get<string>("accessToken"),
                req->attributes()->get<int64_t>("userId")
        ));
    }, response);
    response.httpCallback(callback);
}