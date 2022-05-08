//
// Created by particleg on 2021/9/29.
//

#pragma once

#include <drogon/drogon.h>
#include <helpers/RedisHelper.h>
#include <structures/RedisToken.h>
#include <types/DataType.h>

namespace mnemosyne::structures {
    class DataRedis : public helpers::RedisHelper {
    public:
        explicit DataRedis();

        bool dataStar(int64_t userId, int64_t dataId); /// True is starred, false otherwise

    private:
    };
}
