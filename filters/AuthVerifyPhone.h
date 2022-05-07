//
// Created by particleg on 2021/9/27.
//

#pragma once

#include <drogon/HttpFilter.h>
#include <structures/ExceptionHandlers.h>

/**
 * @brief This filter checks "Auth::verifyPhone" request body.
 * @param phone: String
 * @return requestJson: in request attributes
 */

namespace mnemosyne::filters {
    class AuthVerifyPhone :
            public drogon::HttpFilter<AuthVerifyPhone>,
            public structures::RequestJsonHandler<AuthVerifyPhone> {
    public:
        static constexpr char projectName[] = CMAKE_PROJECT_NAME;

    public:
        void doFilter(
                const drogon::HttpRequestPtr &req,
                drogon::FilterCallback &&failedCb,
                drogon::FilterChainCallback &&nextCb
        ) override;
    };
}