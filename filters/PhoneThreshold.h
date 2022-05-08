//
// Created by particleg on 2021/9/27.
//

#pragma once

#include <drogon/HttpFilter.h>
#include <helpers/I18nHelper.h>

/**
 * @brief This filter checks request frequency from specific phone number
 * @param phone: String
 */
namespace mnemosyne::filters {
    class PhoneThreshold :
            public drogon::HttpFilter<PhoneThreshold>,
            public helpers::I18nHelper<PhoneThreshold> {
    public:
        static constexpr char projectName[] = CMAKE_PROJECT_NAME;

        void doFilter(
                const drogon::HttpRequestPtr &req,
                drogon::FilterCallback &&failedCb,
                drogon::FilterChainCallback &&nextCb
        ) override;
    };
}