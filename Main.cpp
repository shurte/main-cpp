#include <Controller.hpp>
#include <FrameManager.hpp>
#include <Hello.hpp>
// #include <stdlib.h>

int main(int argc, char** argv) {
    const Hello hello;
    // hello.clock();

    std::string directory = hello::getAppDirectory();
    hello.write(directory);

    FrameManager frameManager;
    frameManager.start();
    frameManager.printStartTime();
    int64_t previousFrameMilliseconds = 0;

    for (std::size_t i = 0; i < 10; ++i) {
        int64_t millisecondsFromPrevious = previousFrameMilliseconds + frameManager.getMillisecondsFromPrevious();
        while (millisecondsFromPrevious < 1000) {
            Sleep(1000);
            millisecondsFromPrevious += frameManager.getMillisecondsFromPrevious();
        }

        while (millisecondsFromPrevious > 1000) {
            frameManager.printCurrentTime();
            millisecondsFromPrevious -= 1000;
        }

        previousFrameMilliseconds = millisecondsFromPrevious;
    }

    Controller controller;
    controller.run();

    return 0;
}