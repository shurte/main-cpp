#pragma once

#include <GeometricObject.hpp>
#include <Window.hpp>

#include <vector>

class Controller {
    public:
        Controller() {

        }

        void run() {
            init();
            runLoop();
            finish();
        }
        
    private:
        void init();
        void runLoop();
        void finish();

    private:
        std::vector<GeometricObject> getGeometricObjects();

    private:
        Window window;
        std::vector<GeometricObject> geometricObjects;
};