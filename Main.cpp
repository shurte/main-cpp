#include <Hello.hpp>
#include <Controller.hpp>

int main(int argc, char** argv) {
    Hello hello;
    hello.clock();

    std::string directory = hello::getAppDirectory();
    hello.write(directory);

    Controller controller;
    controller.run();

    return 0;
}