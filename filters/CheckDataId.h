//
// Created by particleg on 2021/9/27.
//

#pragma once

#include <drogon/HttpFilter.h>
#include <helpers/I18nHelper.h>

/**
 * @brief This filter checks param "dataId" and set attribute "dataId"
 * @param dataId: in query string
 * @return dataId: Int64
 */

namespace mnemosyne::filters {
    class CheckDataId :
            public drogon::HttpFilter<CheckDataId>,
            public helpers::I18nHelper<CheckDataId> {
    public:
        static constexpr char projectName[] = CMAKE_PROJECT_NAME;

        void doFilter(
                const drogon::HttpRequestPtr &req,
                drogon::FilterCallback &&failedCb,
                drogon::FilterChainCallback &&nextCb
        ) override;
    };
}