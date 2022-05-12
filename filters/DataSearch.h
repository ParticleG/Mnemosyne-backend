//
// Created by particleg on 2021/9/27.
//

#pragma once

#include <drogon/HttpFilter.h>
#include <structures/ExceptionHandlers.h>

/**
 * @brief This filter trims "Data::search" request body
 * @param name: String
 * @param description: String
 * @param tags: Array
 * @param extra: String
 * @param creator: Int64
 * @param fromTime: timestamp
 * @param endTime: timestamp
 * @param page: UInt64
 * @param perPage: UInt64
 * @return requestJson: in request attributes
 */
namespace mnemosyne::filters {
    class DataSearch :
            public drogon::HttpFilter<DataSearch>,
            public structures::RequestJsonHandler<DataSearch> {
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