#pragma once

#define SDL_MAIN_HANDLED
#include <SDL.h>

#include <GL/glew.h>

#include <vector>

struct GeometricObject;

class Window {
    public:
        Window();
        ~Window();

        void update();

    private:
        void initObjects();
        void drawObjects();
        void drawObject(const GeometricObject& geometricObject);

    private:
        SDL_Window* window = nullptr;
        std::vector<GeometricObject> geometricObjects;
};