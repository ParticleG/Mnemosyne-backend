//
// Created by particleg on 2021/9/29.
//

#include <structures/UserRedis.h>
#include <utils/crypto.h>

using namespace drogon;
using namespace std;
using namespace cpp_redis;
using namespace mnemosyne::structures;
using namespace mnemosyne::utils;

// TODO: Make some Redis actions run in pipeline

UserRedis::UserRedis(Expiration expiration) : RedisHelper("user"), _expiration(expiration) {}

UserRedis::UserRedis(UserRedis &&redis) noexcept: RedisHelper("user"), _expiration(redis._expiration) {}

RedisToken UserRedis::refresh(const string &refreshToken) {
    expire("auth:refresh:" + refreshToken, _expiration.refresh);
    return {
            refreshToken,
            _generateAccessToken(get("auth:refresh:" + refreshToken))
    };
}

RedisToken UserRedis::generateTokens(const string &userId) {
    return {
            _generateRefreshToken(userId),
            _generateAccessToken(userId)
    };
}

bool UserRedis::checkEmailCode(const string &email, const string &code) {
    return get("auth:code:email:" + email) == code;
}

bool UserRedis::checkPhoneCode(const string &phone, const string &code) {
    return get("auth:code:phone:" + phone) == code;
}

void UserRedis::deleteEmailCode(const string &email) {
    del("auth:code:email:" + email);
}

void UserRedis::deletePhoneCode(const string &phone) {
    del("auth:code:phone:" + phone);
}

void UserRedis::setEmailCode(const string &email, const string &code) {
    setEx(
            "auth:code:email:" + email,
            _expiration.getEmailSeconds(),
            code
    );
}

void UserRedis::setPhoneCode(const string &phone, const string &code) {
    setEx(
            "auth:code:phone:" + phone,
            _expiration.getPhoneSeconds(),
            code
    );
}

int64_t UserRedis::getIdByAccessToken(const string &accessToken) {
    return stoll(get("auth:access:" + accessToken));
}

Json::Value UserRedis::getFollows(const string &userId) {
    Json::Value result;
    const auto follows = setGetMembers(
            {"user:following:" + userId,
             "user:followers:" + userId}
    );
    for (const auto &following: follows[0]) {
        result["following"].append(stoll(following));
    }
    for (const auto &follower: follows[1]) {
        result["followers"].append(stoll(follower));
    }
    return result;
}

bool UserRedis::follow(const string &userId, const string &followId) {
    if (setIsMember("user:following:" + userId, followId)) {
        setRemove({{"user:following:" + userId,   {followId}},
                   {"user:followers:" + followId, {userId}}});
        return false;
    } else {
        setAdd({{"user:following:" + userId,   {followId}},
                {"user:followers:" + followId, {userId}}});
        return true;
    }
}

Json::Value UserRedis::getStarred(const string &userId) {
    Json::Value result;
    const auto starred = setGetMembers("user:starred:" + userId);
    for (const auto &dataId: starred) {
        result["following"].append(stoll(dataId));
    }
    return result;
}

void UserRedis::dataStar(const string &userId, const string &dataId) {
    if (setIsMember("user:starred:" + userId, dataId)) {
        setRemove("user:starred:" + userId, {dataId});
    } else {
        setAdd("user:starred:" + userId, {dataId});
    }
}

string UserRedis::_generateRefreshToken(const string &userId) {
    auto refreshToken = crypto::keccak(drogon::utils::getUuid());
    setEx(
            "auth:refresh:" + refreshToken,
            _expiration.getRefreshSeconds(),
            userId
    );
    return refreshToken;
}

string UserRedis::_generateAccessToken(const string &userId) {
    auto accessToken = crypto::blake2B(drogon::utils::getUuid());
    setEx({{
                   "auth:id:" + userId,
                   _expiration.getAccessSeconds(),
                   accessToken
           },
           {
                   "auth:access:" + accessToken,
                   _expiration.getAccessSeconds(),
                   userId
           }});
    return accessToken;
}



