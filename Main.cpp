#include <Hello.hpp>
#include <Window.hpp>

class Controller {
    public:
        Controller() {

        }

        void run() {
            window.update();        
        }
    
    private:
        Window window;
};

int main(int argc, char** argv) {
    Hello hello;

    std::string directory = hello::getAppDirectory();
    hello.write(directory);

    Controller controller;
    controller.run();

    return 0;
}