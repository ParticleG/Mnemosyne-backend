//
// Created by Parti on 2021/2/4.
//

#include <drogon/drogon.h>
#include <plugins/Configurator.h>

using namespace drogon;
using namespace std;
using namespace mnemosyne::plugins;

void Configurator::initAndStart(const Json::Value &config) {
    const auto url = "http://localhost:" + to_string(app().getListeners()[0].toPort());

    LOG_INFO << "Webpage URL: " << url;

    LOG_INFO << "Configurator loaded.";

    if (config["cors"].isBool() && config["cors"].asBool()) {
        app().registerSyncAdvice([](const HttpRequestPtr &req) -> HttpResponsePtr {
            if (req->method() == Options) {
                auto resp = HttpResponse::newHttpResponse();
                resp->addHeader("Access-Control-Allow-Origin", "*");
                resp->addHeader("Access-Control-Allow-Headers", req->getHeader("Access-Control-Request-Headers"));
                resp->addHeader("Access-Control-Allow-Methods", req->getHeader("Access-Control-Request-Method"));
                return resp;
            }
            return nullptr;
        });
        app().registerPostHandlingAdvice(
                [](const HttpRequestPtr &req, const HttpResponsePtr &resp) {
                    resp->addHeader("Access-Control-Allow-Origin", "*");
                    resp->addHeader("Access-Control-Allow-Headers", req->getHeader("Access-Control-Request-Headers"));
                    resp->addHeader("Access-Control-Allow-Methods", req->getHeader("Access-Control-Request-Method"));
                }
        );
        return;
    }
}

void Configurator::shutdown() { LOG_INFO << "Configurator shutdown."; }