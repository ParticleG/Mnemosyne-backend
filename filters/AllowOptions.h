//
// Created by particleg on 2021/9/27.
//

#pragma once

#include <drogon/HttpFilter.h>
#include <helpers/I18nHelper.h>

/**
 * @brief This filter allows the client to specify the options for the response.
 */

namespace mnemosyne::filters {
    class AllowOptions :
            public drogon::HttpFilter<AllowOptions>,
            public helpers::I18nHelper<AllowOptions> {
    public:
        static constexpr char projectName[] = CMAKE_PROJECT_NAME;

        void doFilter(
                const drogon::HttpRequestPtr &req,
                drogon::FilterCallback &&failedCb,
                drogon::FilterChainCallback &&nextCb
        ) override;
    };
}