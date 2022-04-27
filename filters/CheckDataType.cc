//
// Created by particleg on 2021/9/27.
//

#include <filters/CheckDataType.h>
#include <helpers/ResponseJson.h>
#include <magic_enum.hpp>
#include <types/DataType.h>

using namespace drogon;
using namespace magic_enum;
using namespace std;
using namespace mnemosyne::filters;
using namespace mnemosyne::helpers;
using namespace mnemosyne::types;

void CheckDataType::doFilter(
        const HttpRequestPtr &req,
        FilterCallback &&failedCb,
        FilterChainCallback &&nextCb
) {
    const auto &dataType = req->getParameter("dataType");
    if (enum_cast<DataType>(dataType).has_value()) {
        req->attributes()->insert("dataType", dataType);
        nextCb();
    } else {
        ResponseJson response;
        response.setStatusCode(k406NotAcceptable);
        response.setResultCode(ResultCode::notAcceptable);
        response.setMessage(i18n("invalidNodeType"));
        response.httpCallback(failedCb);
    }
}
