//
// Created by particleg on 2021/9/29.
//

#include <structures/DataRedis.h>

using namespace drogon;
using namespace std;
using namespace cpp_redis;
using namespace mnemosyne::structures;

// TODO: Make some Redis actions run in pipeline

DataRedis::DataRedis() : RedisHelper("data") {}

void DataRedis::uploadData(
        int64_t userId,
        int64_t dataId,
        const Json::Value &tags
) {
    setAdd(
            "data:posts:" + to_string(userId),
            {to_string(dataId)}
    );
    for (const auto &tag: tags) {
        if (tag.isString()) {
            setAdd(
                    "data:tags:" + tag.asString(),
                    {to_string(dataId)}
            );
        }
    }
}

void DataRedis::deleteData(
        int64_t userId,
        int64_t dataId,
        const Json::Value &tags
) {
    setRemove(
            "data:posts:" + to_string(userId),
            {to_string(dataId)}
    );
    for (const auto &tag: tags) {
        if (tag.isString()) {
            setRemove(
                    "data:tags:" + tag.asString(),
                    {to_string(dataId)}
            );
        }
    }
}
