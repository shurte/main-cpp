#include <Controller.hpp>
#include <FrameManager.hpp>
#include <Hello.hpp>

constexpr int64_t millisecondsInHalfFrame = 1000 / 120;
constexpr int64_t nanosecondsInHalfFrame = millisecondsInHalfFrame * 1000;

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

    Controller controller;
    controller.run();

    return 0;
}