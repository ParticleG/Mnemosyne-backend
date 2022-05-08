//
// Created by ParticleG on 2022/5/8.
//

#pragma once

#include <helpers/RequestJson.h>

namespace mnemosyne::utils::postgresql {
    std::string toPgArray(const helpers::RequestJson &requestJson);
}