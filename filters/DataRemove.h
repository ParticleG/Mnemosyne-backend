//
// Created by particleg on 2021/9/27.
//

#pragma once

#include <drogon/HttpFilter.h>
#include <structures/ExceptionHandlers.h>

/**
 * @brief This filter checks "Data::remove" request body
 * @param id: Int64
 * @return requestJson: in request attributes
 */
namespace mnemosyne::filters {
    class DataRemove :
            public drogon::HttpFilter<DataRemove>,
            public structures::RequestJsonHandler<DataRemove> {
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