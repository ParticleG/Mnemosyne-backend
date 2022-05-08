//
// Created by particleg on 2021/9/27.
//

#pragma once

#include <drogon/HttpFilter.h>
#include <structures/ExceptionHandlers.h>

/**
 * @brief This filter checks "Data::upload" request body
 * @param name: String
 * @param description: String
 * @param tags: Array
 * @param content: String
 * @param extra: String
 * @param preview: String
 * @param collection: Int64
 * @param visibility: Int
 * @return requestJson: in request attributes
 */
namespace mnemosyne::filters {
    class DataUpload :
            public drogon::HttpFilter<DataUpload>,
            public structures::RequestJsonHandler<DataUpload> {
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