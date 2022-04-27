//
// Created by ParticleG on 2022/2/9.
//

#include <structures/Exceptions.h>
#include <helpers/RedisHelper.h>
#include <utils/crypto.h>
#include <utils/datetime.h>

using namespace cpp_redis;
using namespace drogon;
using namespace std;
using namespace mnemosyne::helpers;
using namespace mnemosyne::structures;
using namespace mnemosyne::utils;

RedisHelper::RedisHelper(std::string BaseKey) : _baseKey(std::move(BaseKey)) {}

void RedisHelper::connect(
        const string &host,
        size_t port,
        int db,
        uint32_t timeout,
        int32_t retries,
        uint32_t interval
) {
    _redisClient.connect(
            host,
            port,
            [=, this](const string &host, size_t port, client::connect_state status) {
                if (status == client::connect_state::dropped) {
                    LOG_ERROR << "client disconnected from " << host << ":" << port;
                    connect(host, port, db, timeout, retries, interval);
                } else if (status == client::connect_state::ok) {
                    _redisClient.select(db);
                    _redisClient.sync_commit();
                }
            },
            timeout,
            retries,
            interval
    );
    LOG_INFO << "Redis connected.";
}

void RedisHelper::disconnect() {
    if (_redisClient.is_connected()) {
        _redisClient.disconnect();
        LOG_INFO << "Redis disconnected.";
    }
}

// Make this method safe and efficient.
bool RedisHelper::tokenBucket(
        const string &key,
        const chrono::microseconds &restoreInterval,
        const uint64_t &maxCount
) {
    const auto countKey = _baseKey + ":tokenBucket:count:" + key;
    const auto updatedKey = _baseKey + ":tokenBucket:updated:" + key;

    auto maxTtl = chrono::duration_cast<chrono::seconds>(restoreInterval * maxCount);

    uint64_t countValue;
    try {
        auto bucketCount = get(countKey);
        countValue = stoull(bucketCount);
    } catch (...) {
        _redisClient.set(countKey, to_string(maxCount - 1));
        countValue = maxCount;
    }

    bool hasToken = true;
    try {
        auto lastUpdated = get(updatedKey);
        auto nowMicroseconds = datetime::toDate().microSecondsSinceEpoch();
        auto generatedCount =
                (nowMicroseconds -
                 datetime::toDate(lastUpdated).microSecondsSinceEpoch()
                ) / restoreInterval.count() - 1;

        if (generatedCount >= 1) {
            _redisClient.set(updatedKey, datetime::toString(nowMicroseconds));
            _redisClient.incrby(countKey, static_cast<int>(generatedCount) - 1);
            hasToken = true;
        } else if (countValue > 0) {
            _redisClient.decr(countKey);
            hasToken = true;
        } else {
            hasToken = false;
        }
    } catch (...) {
        _redisClient.set(updatedKey, datetime::toString());
        _redisClient.set(countKey, to_string(maxCount - 1));
    }

    expire(countKey, maxTtl);
    expire(updatedKey, maxTtl);
    return hasToken;
}

void RedisHelper::compare(const string &key, const string &value) {
    if (get(key) != value) {
        throw redis_exception::NotEqual("key = " + key);
    }
}

void RedisHelper::del(const string &key) {
    _redisClient.del({key});
    _redisClient.sync_commit();
}

void RedisHelper::expire(const string &key, const chrono::seconds &ttl) {
    auto future = _redisClient.expire(key, static_cast<int>(ttl.count()));
    _redisClient.sync_commit();
    auto reply = future.get();
    if (reply.is_null()) {
        throw redis_exception::KeyNotFound("Key = " + key);
    }
}

string RedisHelper::get(const string &key) {
    auto future = _redisClient.get(key);
    _redisClient.sync_commit();
    auto reply = future.get();
    if (reply.is_null()) {
        throw redis_exception::KeyNotFound("Key = " + key);
    }
    return reply.as_string();
}

void RedisHelper::setAdd(const string &key, const vector<string> &values) {
    _redisClient.sadd(key, values);
    _redisClient.sync_commit();
}

void RedisHelper::setRemove(const string &key, const vector<string> &values) {
    _redisClient.srem(key, values);
    _redisClient.sync_commit();
}

void RedisHelper::set(const string &key, const string &value) {
    _redisClient.set(key, value);
    _redisClient.sync_commit();
}

void RedisHelper::setEx(const string &key, const int &ttl, const string &value) {
    _redisClient.setex(key, ttl, value);
    _redisClient.sync_commit();
}