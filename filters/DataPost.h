//
// Created by particleg on 2021/9/27.
//

#pragma once

#include <drogon/HttpFilter.h>
#include <structures/ExceptionHandlers.h>

/**
 * @brief This filter checks "Data::post" request body
 * @param type: String
 * @param name: String
 * @param description: String
 * @param tags: Array
 * @param content: String
 * @param extra: String
 * @param collection: Int64
 * @return requestJson: in request attributes
 */
namespace mnemosyne::filters {
    class DataPost :
            public drogon::HttpFilter<DataPost>,
            public structures::RequestJsonHandler<DataPost> {
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