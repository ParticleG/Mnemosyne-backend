//
// Created by particleg on 2021/9/27.
//

#include <filters/DataFuzzy.h>
#include <helpers/RequestJson.h>

using namespace drogon;
using namespace std;
using namespace mnemosyne::filters;
using namespace mnemosyne::helpers;
using namespace mnemosyne::types;

void DataFuzzy::doFilter(
        const HttpRequestPtr &req,
        FilterCallback &&failedCb,
        FilterChainCallback &&nextCb
) {
    handleExceptions([&]() {
        auto request = RequestJson(req);
        request.trim("type", JsonValue::String);
        request.require("query", JsonValue::String);
        request.trim("startTime", JsonValue::String);
        request.trim("endTime", JsonValue::String);
        request.trim("page", JsonValue::UInt64);
        request.trim("perPage", JsonValue::UInt64);
        req->attributes()->insert("requestJson", request);
        nextCb();
    }, failedCb);
}
