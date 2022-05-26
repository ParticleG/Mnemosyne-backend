//
// Created by particleg on 2021/9/27.
//

#include <filters/CollectionModify.h>
#include <helpers/RequestJson.h>
#include <types/DataType.h>

using namespace drogon;
using namespace std;
using namespace mnemosyne::filters;
using namespace mnemosyne::helpers;
using namespace mnemosyne::types;

void CollectionModify::doFilter(
        const HttpRequestPtr &req,
        FilterCallback &&failedCb,
        FilterChainCallback &&nextCb
) {
    handleExceptions([&]() {
        auto request = RequestJson(req);
        request.require("id", JsonValue::Int64);
        request.trim("name", JsonValue::String);
        request.trim("description", JsonValue::String);
        request.trim("tags", JsonValue::Array);
        request.trim("content", JsonValue::Array);
        request.trim("extra", JsonValue::String);
        request.trim("preview", JsonValue::String);
        request.remove("created");
        req->attributes()->insert("requestJson", request);
        nextCb();
    }, failedCb);
}
