//
// Created by particleg on 2021/9/27.
//

#include <filters/PhoneThreshold.h>
#include <helpers/RequestJson.h>
#include <helpers/ResponseJson.h>
#include <plugins/UserManager.h>
#include <structures/Exceptions.h>

using namespace drogon;
using namespace std;
using namespace mnemosyne::filters;
using namespace mnemosyne::helpers;
using namespace mnemosyne::plugins;
using namespace mnemosyne::structures;
using namespace mnemosyne::types;

void mnemosyne::filters::PhoneThreshold::doFilter(
        const HttpRequestPtr &req,
        FilterCallback &&failedCb,
        FilterChainCallback &&nextCb
) {
    auto requestJson = req->attributes()->get<RequestJson>("requestJson");
    try {
        if (!app().getPlugin<UserManager>()->phoneLimit(requestJson["phone"].asString())) {
            ResponseJson response;
            response.setStatusCode(k429TooManyRequests);
            response.setResultCode(ResultCode::tooFrequent);
            response.setMessage(i18n("tooFrequent"));
            response.httpCallback(failedCb);
            return;
        }
    } catch (const exception &e) {
        LOG_ERROR << e.what();
        ResponseJson response;
        response.setStatusCode(k500InternalServerError);
        response.setResultCode(ResultCode::internalError);
        response.setMessage(i18n("internalError"));
        response.httpCallback(failedCb);
        return;
    }
    nextCb();
}
