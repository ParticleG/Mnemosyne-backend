//
// Created by ParticleG on 2022/5/8.
//

#pragma once

#include <drogon/orm/Criteria.h>
#include <format>
#include <helpers/RequestJson.h>

namespace mnemosyne::utils::postgresql {
    std::string toPgArray(const helpers::RequestJson &requestJson);

    template<typename... Arguments>
    drogon::orm::CustomSql toCustomSql(const std::string &fmt, Arguments &&... arguments) {
        return drogon::orm::CustomSql{
            std::format(fmt, std::forward<Arguments>(arguments)...)
        };
    }
}