//
// Created by particleg on 2021/9/29.
//

#include <structures/DataRedis.h>

using namespace drogon;
using namespace std;
using namespace cpp_redis;
using namespace mnemosyne::structures;
using namespace mnemosyne::types;

DataRedis::DataRedis(Expiration expiration) : RedisHelper("data"), _expiration(expiration) {}

DataRedis::DataRedis(DataRedis &&redis) noexcept: RedisHelper("data"), _expiration(redis._expiration) {}