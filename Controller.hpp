#pragma once

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