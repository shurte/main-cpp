#pragma once

#include <GeometricObject.hpp>

#define SDL_MAIN_HANDLED
#include <SDL.h>

#include <GL/glew.h>

#include <vector>

class Window {
    public:
        Window();
        ~Window();

        void update();
        void setGeometricObjects(const std::vector<GeometricObject>& geometricObjects);
        size_t getCurrentEvent();

    private:
        void initObjects();
        void drawObjects();
        void drawObject(const GeometricObject& geometricObject);

    private:
        SDL_Window* window = nullptr;
        std::vector<GeometricObject> geometricObjects;
        size_t currentEvent = 0;
};