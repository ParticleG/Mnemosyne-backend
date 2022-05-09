//
// Created by particleg on 2021/9/27.
//

#pragma once

#include <drogon/HttpFilter.h>
#include <structures/ExceptionHandlers.h>

/**
 * @brief This filter trims "Collection::fuzzy" request body
 * @param query: String
 * @param fromTime: timestamp
 * @param endTime: timestamp
 * @param page: UInt64
 * @param perPage: UInt64
 * @return requestJson: in request attributes
 */
namespace mnemosyne::filters {
    class CollectionFuzzy :
            public drogon::HttpFilter<CollectionFuzzy>,
            public structures::RequestJsonHandler<CollectionFuzzy> {
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