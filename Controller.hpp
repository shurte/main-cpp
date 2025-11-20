#pragma once

#include <GeometricObject.hpp>
#include <Window.hpp>

#include <vector>

class Controller {
    public:
        Controller() {

        }

        void run() {
            window.setGeometricObjects(getGeometricObjects());
            window.update();
        }
        
    private:
        std::vector<GeometricObject> getGeometricObjects();

    private:
        Window window;
};