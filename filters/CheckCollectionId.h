//
// Created by particleg on 2021/9/27.
//

#pragma once

#include <drogon/HttpFilter.h>
#include <helpers/I18nHelper.h>

/**
 * @brief This filter checks param "collectionId" and set attribute "collectionId"
 * @param collectionId: in query string
 * @return collectionId: Int64
 */

namespace mnemosyne::filters {
    class CheckCollectionId :
            public drogon::HttpFilter<CheckCollectionId>,
            public helpers::I18nHelper<CheckCollectionId> {
    public:
        static constexpr char projectName[] = CMAKE_PROJECT_NAME;

        void doFilter(
                const drogon::HttpRequestPtr &req,
                drogon::FilterCallback &&failedCb,
                drogon::FilterChainCallback &&nextCb
        ) override;
    };
}