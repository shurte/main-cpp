#include <Hello.hpp>
#include <Window.hpp>

int main(int argc, char** argv) {
    Hello hello;

    std::string directory = hello::getAppDirectory();
    hello.write(directory);

    Window window;
    window.update();

    return 0;
}