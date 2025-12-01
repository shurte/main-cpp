#pragma once

#include <GameObject.hpp>
#include <GeometricObject.hpp>
#include <Window.hpp>

#include <vector>

#define WINDOW_SIZE_H 1200
#define WINDOW_SIZE_V 600

class Controller {
    public:
        Controller() 
            : window(WINDOW_SIZE_H, WINDOW_SIZE_V) {

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
        std::vector<GameObject> gameObjects;
        std::vector<GeometricObject> geometricObjects;
};