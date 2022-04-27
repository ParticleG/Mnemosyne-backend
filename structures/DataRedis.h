//
// Created by particleg on 2021/9/29.
//

#pragma once

#include <drogon/drogon.h>
#include <helpers/RedisHelper.h>
#include <structures/RedisToken.h>

namespace mnemosyne::structures {
    class DataRedis : public helpers::RedisHelper {
    public:
        explicit DataRedis();

        void uploadData(
                int64_t userId,
                int64_t dataId,
                const Json::Value &tags
        );

        void deleteData(
                int64_t userId,
                int64_t dataId,
                const Json::Value &tags
        );

    private:
    };
}
