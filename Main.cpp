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
    frameManager.printCurrentTime();
    int64_t startFrames = frameManager.getFramesFromStart();

    for (std::size_t i = 0; i < 10; ++i) {
        int64_t currentFrames = frameManager.getFramesFromStart();
        while (currentFrames - startFrames < 60) {
            Sleep(1000 / 120);
            currentFrames = frameManager.getFramesFromStart();
        }

        while (currentFrames > startFrames) {
            frameManager.printCurrentTime();
            std::cout << "Start frames: " << startFrames << '\n';
            std::cout << "Current frames: " << currentFrames << '\n' << '\n';
            startFrames += 60;
        }
    }

    Controller controller;
    controller.run();

    return 0;
}