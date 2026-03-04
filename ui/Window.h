#pragma once

#include <UiObject.h>

#define SDL_MAIN_HANDLED
#include <SDL.h>

#include <GL/glew.h>

#include <vector>

#define WINDOW_MOUSE_DOWN 1
#define WINDOW_MOUSE_UP 2
#define WINDOW_MOVE_UP 3
#define WINDOW_MOVE_DOWN 4
#define WINDOW_MOVE_RIGHT 5
#define WINDOW_MOVE_LEFT 6
#define WINDOW_EXIT 128

class Window {
    public:
        Window(size_t sizeHorizontal, size_t sizeVertical);
        ~Window();

        void init();
        void update();
        void setUiObjects(const std::vector<UiObject>& geometricObjects);
        size_t getCurrentEvent();

    private:
        void updateEvent();
        void redraw();
        void drawObjects();
        void drawObject(const UiObject& geometricObject);

    private:
        SDL_Window* window = nullptr;
        std::vector<UiObject> uiObjects;
        size_t currentEvent = 0;
};