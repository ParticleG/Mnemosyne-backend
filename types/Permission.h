//
// Created by ParticleG on 2022/3/11.
//

#pragma once

#include <drogon/drogon.h>

namespace mnemosyne::types {
    enum class Permission {
        Banned,
        Restricted,
        Normal,
        Admin
    };
}