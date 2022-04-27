//
// Created by Parti on 2021/2/4.
//

#pragma once

#include <drogon/plugins/Plugin.h>

namespace mnemosyne::plugins {
    class Configurator : public drogon::Plugin<Configurator> {
    public:
        Configurator() = default;

        void initAndStart(const Json::Value &config) override;

        void shutdown() override;
    };
}

