//
// Created by particleg on 2021/9/27.
//

#include <filters/DataPost.h>
#include <helpers/RequestJson.h>

using namespace drogon;
using namespace std;
using namespace mnemosyne::filters;
using namespace mnemosyne::helpers;
using namespace mnemosyne::types;

void DataPost::doFilter(
        const HttpRequestPtr &req,
        FilterCallback &&failedCb,
        FilterChainCallback &&nextCb
) {
    handleExceptions([&]() {
        auto request = RequestJson(req);
        request.trim("type", JsonValue::String);
        request.trim("name", JsonValue::String);
        request.trim("description", JsonValue::String);
        request.trim("tags", JsonValue::Array);
        request.require("content", JsonValue::String);
        request.trim("extra", JsonValue::String);
        request.trim("collection", JsonValue::Int64);
        req->attributes()->insert("requestJson", request);
        nextCb();
    }, failedCb);
}
