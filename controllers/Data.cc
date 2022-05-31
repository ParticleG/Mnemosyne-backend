//
// Created by particleg on 2021/9/24.
//

#include <controllers/Data.h>
#include <helpers/ResponseJson.h>
#include <types/DataType.h>

using namespace drogon;
using namespace std;
using namespace mnemosyne::api::v1;
using namespace mnemosyne::helpers;
using namespace mnemosyne::plugins;
using namespace mnemosyne::structures;
using namespace mnemosyne::types;

Data::Data() :
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

void Data::post(const HttpRequestPtr &req, function<void(const HttpResponsePtr &)> &&callback) {
    ResponseJson response;
    handleExceptions([&]() {
        response.setData(_dataManager->dataPost(
                req->attributes()->get<RequestJson>("requestJson")
        ));
    }, response);
    response.httpCallback(callback);
}

void Data::upload(const HttpRequestPtr &req, function<void(const HttpResponsePtr &)> &&callback) {
    ResponseJson response;
    handleExceptions([&]() {
        response.setData(_dataManager->dataUpload(
                req->attributes()->get<RequestJson>("requestJson"),
                req->attributes()->get<vector<HttpFile>>("files")[0]
        ));
    }, response);
    response.httpCallback(callback);
}

void Data::fuzzy(const HttpRequestPtr &req, function<void(const HttpResponsePtr &)> &&callback) {
    ResponseJson response;
    handleExceptions([&]() {
        response.setData(_dataManager->dataFuzzy(
                req->attributes()->get<RequestJson>("requestJson")
        ));
    }, response);
    response.httpCallback(callback);
}

void Data::search(const HttpRequestPtr &req, function<void(const HttpResponsePtr &)> &&callback) {
    ResponseJson response;
    handleExceptions([&]() {
        response.setData(_dataManager->dataSearch(
                req->attributes()->get<RequestJson>("requestJson")
        ));
    }, response);
    response.httpCallback(callback);
}

void Data::info(const HttpRequestPtr &req, function<void(const HttpResponsePtr &)> &&callback) {
    ResponseJson response;
    handleExceptions([&]() {
        response.setData(_dataManager->dataInfo(
                req->attributes()->get<int64_t>("dataId")
        ));
    }, response);
    response.httpCallback(callback);
}

void Data::modify(const HttpRequestPtr &req, function<void(const HttpResponsePtr &)> &&callback) {
    ResponseJson response;
    handleExceptions([&]() {
        _dataManager->dataModify(
                req->attributes()->get<RequestJson>("requestJson")
        );
    }, response);
    response.httpCallback(callback);
}

void Data::remove(const HttpRequestPtr &req, function<void(const HttpResponsePtr &)> &&callback) {
    ResponseJson response;
    handleExceptions([&]() {
        _dataManager->dataDelete(
                req->attributes()->get<int64_t>("dataId")
        );
    }, response);
    response.httpCallback(callback);
}