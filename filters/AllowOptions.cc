//
// Created by particleg on 2021/9/27.
//

#include <filters/AllowOptions.h>
#include <helpers/ResponseJson.h>

using namespace drogon;
using namespace std;
using namespace mnemosyne::filters;
using namespace mnemosyne::helpers;

void AllowOptions::doFilter(
        const HttpRequestPtr &req,
        FilterCallback &&failedCb,
        FilterChainCallback &&nextCb
) {
    if (req->method() == Options) {
        ResponseJson().httpCallback(failedCb, "*");
        return;
    }
    nextCb();
}


