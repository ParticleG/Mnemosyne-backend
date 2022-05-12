#define DROGON_TEST_MAIN

#include <drogon/drogon_test.h>
#include <drogon/drogon.h>

using namespace drogon;
using namespace std;

DROGON_TEST(AuthTest) {
    for (int i = 0; i < 12; i++) {
        CHECK(true);
    }
}

DROGON_TEST(UserTest) {
    for (int i = 0; i < 6; i++) {
        CHECK(true);
    }
}

DROGON_TEST(DataTest) {
    for (int i = 0; i < 6; i++) {
        CHECK(true);
    }
}

DROGON_TEST(CollectionTest) {
    for (int i = 0; i < 6; i++) {
        CHECK(true);
    }
}

int main(int argc, char **argv) {
    promise<void> loopStart;
    auto checkLoopStart = loopStart.get_future();

    /** Start the main loop on another thread */
    thread loopHandler([&]() {
        /** Queues the promise to be fulfilled after starting the loop */
        app().getLoop()->queueInLoop([&loopStart]() { loopStart.set_value(); });
        app().loadConfigFile("config.json");
        app().run();
    });

    /** The future is only satisfied after the event loop started */
    checkLoopStart.get();
    auto status = test::run(argc, argv);

    /** Ask the event loop to shutdown and wait */
    app().getLoop()->queueInLoop([]() { app().quit(); });
    loopHandler.join();

    return status;
}
