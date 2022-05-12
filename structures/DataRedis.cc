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

bool DataRedis::dataStar(const string &userId, const string &dataId) {
    if (setIsMember("starred:data:" + dataId, userId)) {
        setRemove("starred:data:" + dataId, {userId});
        return false;
    } else {
        setAdd("starred:data:" + dataId, {userId});
        return true;
    }
}

bool DataRedis::collectionStar(const string &userId, const string &collectionId) {
    if (setIsMember("starred:collection:" + collectionId, userId)) {
        setRemove("starred:collection:" + collectionId, {userId});
        return false;
    } else {
        setAdd("starred:collection:" + collectionId, {userId});
        return true;
    }
}
