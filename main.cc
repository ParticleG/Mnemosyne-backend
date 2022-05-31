#include <drogon/drogon.h>

using namespace drogon;

int main() {
    app().loadConfigFile("config.no-user.json");
    app().run();
    return 0;
}
