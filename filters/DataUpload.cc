//
// Created by particleg on 2021/9/27.
//

#include <filters/DataUpload.h>
#include <helpers/RequestJson.h>
#include <helpers/ResponseJson.h>
#include <types/ResultCode.h>

using namespace drogon;
using namespace std;
using namespace mnemosyne::filters;
using namespace mnemosyne::helpers;
using namespace mnemosyne::types;

void DataUpload::doFilter(
        const HttpRequestPtr &req,
        FilterCallback &&failedCb,
        FilterChainCallback &&nextCb
) {
    MultiPartParser parser;
    if (parser.parse(req)) {
        ResponseJson response;
        response.setStatusCode(k400BadRequest);
        response.setResultCode(ResultCode::invalidFormat);
        response.setMessage(i18n("invalidFormat"));
        response.httpCallback(failedCb);
        return;
    }

    const auto &files = parser.getFiles();
    if (files.size() != 1) {
        ResponseJson response;
        response.setStatusCode(k406NotAcceptable);
        response.setResultCode(ResultCode::notAcceptable);
        response.setMessage(i18n("fileNotAcceptable"));
        response.httpCallback(failedCb);
        return;
    }
    req->attributes()->insert("files", files);

    Json::Value parameters;
    for (const auto &[key, value]: parser.getParameters()) {
        parameters[key] = value;
    }
    RequestJson requestJson(parameters);
    LOG_DEBUG << requestJson.stringify();

    handleExceptions([&]() {
        requestJson.trim("type", JsonValue::String);
        requestJson.trim("name", JsonValue::String);
        requestJson.trim("description", JsonValue::String);
        requestJson.trim("tags", JsonValue::Array);
        requestJson.trim("extra", JsonValue::String);
        requestJson.trim("collection", JsonValue::Int64);
        req->attributes()->insert("requestJson", requestJson);
        nextCb();
    }, failedCb);

    nextCb();
}


