//
// Created by particleg on 2021/9/27.
//

#include <filters/DataSearch.h>
#include <helpers/RequestJson.h>

using namespace drogon;
using namespace std;
using namespace mnemosyne::filters;
using namespace mnemosyne::helpers;
using namespace mnemosyne::types;

void DataSearch::doFilter(
        const HttpRequestPtr &req,
        FilterCallback &&failedCb,
        FilterChainCallback &&nextCb
) {
    handleExceptions([&]() {
        auto request = RequestJson(req);
        request.trim("name", JsonValue::String);
        request.trim("description", JsonValue::String);
        request.trim("tags", JsonValue::Array);
        request.trim("extra", JsonValue::String);
        request.trim("creator", JsonValue::Int64);
        request.trim("fromTime", JsonValue::String);
        request.trim("endTime", JsonValue::String);
        request.trim("page", JsonValue::UInt64);
        request.ref()["type"] = req->attributes()->get<std::string>("dataType");
        req->attributes()->insert("requestJson", request);
        nextCb();
    }, failedCb);
}
