//
// Created by particleg on 2021/9/27.
//

#include <filters/CheckRefreshToken.h>

using namespace drogon;
using namespace std;
using namespace mnemosyne::filters;

void CheckRefreshToken::doFilter(
        const HttpRequestPtr &req,
        FilterCallback &&failedCb,
        FilterChainCallback &&nextCb
) {
    req->attributes()->insert("refreshToken", req->getHeader("x-refresh-token"));
    nextCb();
}