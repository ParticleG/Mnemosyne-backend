//
// Created by particleg on 2021/9/27.
//

#include <filters/DataUpload.h>
#include <helpers/RequestJson.h>

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
    handleExceptions([&]() {
        auto request = RequestJson(req);
        request.trim("name", JsonValue::String);
        request.trim("tags", JsonValue::Array);
        request.trim("collection", JsonValue::Int64);
        request.require("content", JsonValue::String);
        request.trim("visibility", JsonValue::Int);
        request.trim("extra", JsonValue::String);
        request.ref()["type"] = req->attributes()->get<std::string>("dataType");
        req->attributes()->insert("requestJson", request);
        nextCb();
    }, failedCb);
}
