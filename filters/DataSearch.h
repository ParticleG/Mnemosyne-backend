//
// Created by particleg on 2021/9/27.
//

#pragma once

#include <drogon/HttpFilter.h>
#include <structures/ExceptionHandlers.h>

/**
 * @brief This filter trims "Data::search" request body
 * @param name: String
 * @param tags: Array
 * @param extra: String
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