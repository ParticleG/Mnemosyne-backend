//
// Created by particleg on 2021/9/27.
//

#include <filters/CheckDataId.h>
#include <helpers/ResponseJson.h>
#include <types/ResultCode.h>

using namespace drogon;
using namespace std;
using namespace mnemosyne::filters;
using namespace mnemosyne::helpers;
using namespace mnemosyne::types;

void CheckDataId::doFilter(
        const HttpRequestPtr &req,
        FilterCallback &&failedCb,
        FilterChainCallback &&nextCb
) {
    const auto &dataId = req->getParameter("dataId");
    if (dataId.empty()) {
        ResponseJson response;
        response.setStatusCode(k400BadRequest);
        response.setResultCode(ResultCode::invalidArguments);
        response.setMessage(i18n("invalidArguments"));
        response.httpCallback(failedCb);
        return;
    }
    req->attributes()->insert("dataId", stoll(dataId));
    nextCb();
}


