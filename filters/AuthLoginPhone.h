//
// Created by particleg on 2021/9/27.
//

#pragma once

#include <drogon/HttpFilter.h>
#include <structures/ExceptionHandlers.h>

/**
 * @brief This filter checks "Auth::loginPhone" request body.
 * @param phone: String
 * @param code: String | Optional
 * @param password: String | Optional
 * @return requestJson: in request attributes
 */

namespace mnemosyne::filters {
    class AuthLoginPhone :
            public drogon::HttpFilter<AuthLoginPhone>,
            public structures::RequestJsonHandler<AuthLoginPhone> {
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