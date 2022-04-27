//
// Created by particleg on 2021/9/27.
//

#pragma once

#include <drogon/HttpFilter.h>
#include <structures/ExceptionHandlers.h>

/**
 * @brief This filter trims "Data::fuzzy" request body
 * @param query: String
 * @return requestJson: in request attributes
 */
namespace mnemosyne::filters {
    class DataFuzzy :
            public drogon::HttpFilter<DataFuzzy>,
            public structures::RequestJsonHandler<DataFuzzy> {
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