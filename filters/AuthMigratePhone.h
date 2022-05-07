//
// Created by particleg on 2021/9/27.
//

#pragma once

#include <drogon/HttpFilter.h>
#include <structures/ExceptionHandlers.h>

/**
 * @brief This filter checks "Auth::migratePhone" request body.
 * @param newPhone: String
 * @param code: String
 * @return requestJson: in request attributes
 */

namespace mnemosyne::filters {
    class AuthMigratePhone :
            public drogon::HttpFilter<AuthMigratePhone>,
            public structures::RequestJsonHandler<AuthMigratePhone> {
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