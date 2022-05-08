//
// Created by particleg on 2021/9/29.
//

#include <structures/DataRedis.h>

using namespace drogon;
using namespace std;
using namespace cpp_redis;
using namespace mnemosyne::structures;
using namespace mnemosyne::types;

DataRedis::DataRedis() : RedisHelper("data") {}

bool DataRedis::dataStar(int64_t userId, int64_t dataId) {
    setAdd(
            "data:starred" + to_string(dataId),
            {to_string(userId)}
    );
    return false;
}
