//
// Created by particleg on 2021/9/27.
//

#pragma once

#include <drogon/HttpFilter.h>
#include <structures/ExceptionHandlers.h>

/**
 * @brief This filter checks "Auth::deactivatePhone" request body.
 * @param code: String
 * @return requestJson: in request attributes
 */

namespace mnemosyne::filters {
    class AuthDeactivatePhone :
            public drogon::HttpFilter<AuthDeactivatePhone>,
            public structures::RequestJsonHandler<AuthDeactivatePhone> {
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