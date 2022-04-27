//
// Created by particleg on 2021/9/27.
//

#pragma once

#include <drogon/HttpFilter.h>
#include <helpers/I18nHelper.h>

/**
 * @brief This filter checks url parameter "dataType"
 * @param dataType: in query string
 * @return dataType: in request attributes
 */

namespace mnemosyne::filters {
    class CheckDataType :
            public drogon::HttpFilter<CheckDataType, false>,
            public helpers::I18nHelper<CheckDataType> {
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