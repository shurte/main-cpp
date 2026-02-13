#include <Controller.hpp>

#include <iostream>

/**
 * The main function.
 * @param argc Number of arguments from the command line.
 * @param argv Values of arguments from the command line.
 */
int main(int argc, char** argv) {
    try {
        for (size_t i = 0; i < argc; ++i) {
            std::cout << argv[i] << '\n';
        }

        Controller controller;
        controller.run();

        return 0;
    } catch (...) {
        std::cout << "an unexpected error" << '\n';
        return 1;
    }
}