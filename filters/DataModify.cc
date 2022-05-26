//
// Created by particleg on 2021/9/27.
//

#include <filters/DataModify.h>
#include <helpers/RequestJson.h>

using namespace drogon;
using namespace std;
using namespace mnemosyne::filters;
using namespace mnemosyne::helpers;
using namespace mnemosyne::types;

void DataModify::doFilter(
        const HttpRequestPtr &req,
        FilterCallback &&failedCb,
        FilterChainCallback &&nextCb
) {
    handleExceptions([&]() {
        auto request = RequestJson(req);
        request.require("id", JsonValue::Int64);
        request.trim("type", JsonValue::String);
        request.trim("name", JsonValue::String);
        request.trim("description", JsonValue::String);
        request.trim("tags", JsonValue::Array);
        request.trim("content", JsonValue::String);
        request.trim("extra", JsonValue::String);
        request.trim("preview", JsonValue::String);
        request.trim("collection", JsonValue::Int64);
        request.remove("creator");
        request.remove("created");
        req->attributes()->insert("requestJson", request);
        nextCb();
    }, failedCb);
}
