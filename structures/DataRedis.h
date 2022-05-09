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

        bool dataStar(const std::string &userId, const std::string &dataId); /// True is starred, false otherwise

        bool collectionStar(const std::string &userId, const std::string &collectionId); /// True is starred, false otherwise

    private:
    };
}
