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
        request.trim("tags", JsonValue::Array);
        request.trim("extra", JsonValue::String);
        request.ref()["type"] = req->attributes()->get<std::string>("dataType");
        req->attributes()->insert("requestJson", request);
        nextCb();
    }, failedCb);
}