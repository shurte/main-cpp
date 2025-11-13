#pragma once

#define SDL_MAIN_HANDLED
#include <SDL.h>

#include <GL/glew.h>

class Window {
    public:
        Window();
        ~Window();

        void update();

    private:
        SDL_Window* window = nullptr;
};