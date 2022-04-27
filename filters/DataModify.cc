//
// Created by particleg on 2021/9/27.
//

#include <filters/DataModify.h>
#include <helpers/RequestJson.h>
#include <magic_enum.hpp>
#include <types/DataType.h>

using namespace drogon;
using namespace magic_enum;
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
        request.trim("name", JsonValue::String);
        request.trim("tags", JsonValue::String);
        request.trim("collection", JsonValue::Int64);
        request.trim("content", JsonValue::String);
        request.trim("visibility", JsonValue::Int);
        request.trim("extra", JsonValue::String);

        const auto &dataType = req->getParameter("dataType");
        if (enum_cast<DataType>(dataType).has_value()) {
            request.ref()["type"] = dataType;
        }

        req->attributes()->insert("requestJson", request);
        nextCb();
    }, failedCb);
}
