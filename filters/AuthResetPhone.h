//
// Created by particleg on 2021/9/27.
//

#pragma once

#include <drogon/HttpFilter.h>
#include <structures/ExceptionHandlers.h>

/**
 * @brief This filter checks "Auth::resetPhone" request body.
 * @param phone: String
 * @param code: String
 * @param newPassword: String
 * @return requestJson: in request attributes
 */

namespace mnemosyne::filters {
    class AuthResetPhone :
            public drogon::HttpFilter<AuthResetPhone>,
            public structures::RequestJsonHandler<AuthResetPhone> {
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