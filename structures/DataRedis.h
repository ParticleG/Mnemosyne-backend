//
// Created by particleg on 2021/9/29.
//

#pragma once

#include <drogon/drogon.h>
#include <helpers/RedisHelper.h>
#include <types/DataType.h>

namespace mnemosyne::structures {
    class DataRedis : public helpers::RedisHelper {
    private:
        struct Expiration {
            [[nodiscard]] int getCacheSeconds() const {
                return static_cast<int>(cache.count());
            }

            std::chrono::seconds cache{};
        };

    public:
        explicit DataRedis(Expiration expiration);

        DataRedis(DataRedis &&redis) noexcept;

    private:
        const Expiration _expiration;
    };
}
