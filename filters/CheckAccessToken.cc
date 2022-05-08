//
// Created by particleg on 2021/9/27.
//

#include <filters/CheckAccessToken.h>

using namespace drogon;
using namespace std;
using namespace mnemosyne::filters;

void CheckAccessToken::doFilter(
        const HttpRequestPtr &req,
        FilterCallback &&failedCb,
        FilterChainCallback &&nextCb
) {
    req->attributes()->insert("accessToken", req->getHeader("x-access-token"));
    nextCb();
}


