#include <Controller.hpp>
#include <FrameManager.hpp>
#include <Hello.hpp>

//#ifdef _WIN32
// #include <windows.h>
// #else
// #include <unistd.h>
// #endif
// #include <stdlib.h>

/**
 * The main function.
 * @param argc Number of arguments from the command line.
 * @param argv Values of arguments from the command line.
 */
int main(int argc, char** argv) {
    const Hello hello;
    // hello.clock();

    std::string directory = hello::getAppDirectory();
    hello.write(directory);

    FrameManager frameManager;
    frameManager.start();
    frameManager.printCurrentTime();
    int64_t startFrames = frameManager.getFramesFromStart();

    timespec mySpec, myRem;
    mySpec.tv_nsec = 1000 / 120 * 1000;

    for (std::size_t i = 0; i < 10; ++i) {
        int64_t currentFrames = frameManager.getFramesFromStart();
        while (currentFrames - startFrames < 60) {
            #ifdef _WIN32
            Sleep(1000 / 120);
            #else
            nanosleep(&mySpec, &myRem);
            #endif
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