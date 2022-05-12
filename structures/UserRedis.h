//
// Created by particleg on 2021/9/29.
//

#pragma once

#include <drogon/drogon.h>
#include <helpers/RedisHelper.h>
#include <structures/RedisToken.h>

namespace mnemosyne::structures {
    class UserRedis : public helpers::RedisHelper {
    private:
        struct Expiration {
            [[nodiscard]] int getRefreshSeconds() const {
                return static_cast<int>(refresh.count());
            }

            [[nodiscard]] int getAccessSeconds() const {
                return static_cast<int>(access.count());
            }

            [[nodiscard]] int getEmailSeconds() const {
                return static_cast<int>(email.count());
            }

            [[nodiscard]] int getPhoneSeconds() const {
                return static_cast<int>(phone.count());
            }

            std::chrono::seconds refresh{}, access{}, email{}, phone{};
        };

    public:
        explicit UserRedis(Expiration expiration);

        UserRedis(UserRedis &&redis) noexcept;

        RedisToken refresh(const std::string &refreshToken);

        [[nodiscard]] RedisToken generateTokens(const std::string &userId);

        bool checkEmailCode(const std::string &email, const std::string &code);

        bool checkPhoneCode(const std::string &phone, const std::string &code);

        void deleteEmailCode(const std::string &email);

        void deletePhoneCode(const std::string &phone);

        void setEmailCode(const std::string &email, const std::string &code);

        void setPhoneCode(const std::string &phone, const std::string &code);

        [[nodiscard]] int64_t getIdByAccessToken(const std::string &accessToken);

        Json::Value getFollows(const std::string &userId);

        bool follow(const std::string &userId, const std::string &followId);

        Json::Value getStarred(const std::string &userId);

        void dataStar(const std::string &userId, const std::string &dataId);

        void collectionStar(const std::string &userId, const std::string &collectionId);

        Json::Value getStatistics(const std::string &userId);

    private:
        const Expiration _expiration;

        std::string _generateRefreshToken(const std::string &userId);

        std::string _generateAccessToken(const std::string &userId);
    };
}
