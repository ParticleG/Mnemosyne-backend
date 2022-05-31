//
// Created by particleg on 2021/9/24.
//

#include <controllers/Collection.h>
#include <helpers/ResponseJson.h>
#include <types/DataType.h>

using namespace drogon;
using namespace std;
using namespace mnemosyne::api::v1;
using namespace mnemosyne::helpers;
using namespace mnemosyne::plugins;
using namespace mnemosyne::structures;
using namespace mnemosyne::types;

Collection::Collection() :
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
        _dataManager(app().getPlugin<DataManager>()) {}

void Collection::create(const HttpRequestPtr &req, function<void(const HttpResponsePtr &)> &&callback) {
    ResponseJson response;
    handleExceptions([&]() {
        response.setData(_dataManager->collectionCreate(
                req->attributes()->get<RequestJson>("requestJson")
        ));
    }, response);
    response.httpCallback(callback);
}

void Collection::fuzzy(const HttpRequestPtr &req, function<void(const HttpResponsePtr &)> &&callback) {
    ResponseJson response;
    handleExceptions([&]() {
        response.setData(_dataManager->collectionFuzzy(
                req->attributes()->get<RequestJson>("requestJson")
        ));
    }, response);
    response.httpCallback(callback);
}

void Collection::search(const HttpRequestPtr &req, function<void(const HttpResponsePtr &)> &&callback) {
    ResponseJson response;
    handleExceptions([&]() {
        response.setData(_dataManager->collectionSearch(
                req->attributes()->get<RequestJson>("requestJson")
        ));
    }, response);
    response.httpCallback(callback);
}

void Collection::info(const HttpRequestPtr &req, function<void(const HttpResponsePtr &)> &&callback) {
    ResponseJson response;
    handleExceptions([&]() {
        response.setData(_dataManager->collectionInfo(
                req->attributes()->get<int64_t>("collectionId")
        ));
    }, response);
    response.httpCallback(callback);
}

void Collection::modify(const HttpRequestPtr &req, function<void(const HttpResponsePtr &)> &&callback) {
    ResponseJson response;
    handleExceptions([&]() {
        _dataManager->collectionModify(
                req->attributes()->get<RequestJson>("requestJson")
        );
    }, response);
    response.httpCallback(callback);
}

void Collection::remove(const HttpRequestPtr &req, function<void(const HttpResponsePtr &)> &&callback) {
    ResponseJson response;
    handleExceptions([&]() {
        _dataManager->collectionDelete(
                req->attributes()->get<int64_t>("collectionId")
        );
    }, response);
    response.httpCallback(callback);
}