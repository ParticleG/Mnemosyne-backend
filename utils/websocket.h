//
// Created by Parti on 2021/2/5.
//

#pragma once

#include <drogon/WebSocketController.h>

namespace mnemosyne::utils::websocket {
    void initPing(
            const drogon::WebSocketConnectionPtr &wsConnPtr,
            const Json::Value &initMessage,
            const std::chrono::duration<long double> &interval
    );
}