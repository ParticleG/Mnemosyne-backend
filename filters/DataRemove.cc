//
// Created by particleg on 2021/9/27.
//

#include <filters/DataRemove.h>
#include <helpers/RequestJson.h>

using namespace drogon;
using namespace std;
using namespace mnemosyne::filters;
using namespace mnemosyne::helpers;
using namespace mnemosyne::types;

void DataRemove::doFilter(
        const HttpRequestPtr &req,
        FilterCallback &&failedCb,
        FilterChainCallback &&nextCb
) {
    handleExceptions([&]() {
        auto request = RequestJson(req);
        request.require("id", JsonValue::Int64);
        req->attributes()->insert("requestJson", request);
        nextCb();
    }, failedCb);
}
