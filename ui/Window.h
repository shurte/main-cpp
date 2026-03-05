#pragma once

#include <UiObject.h>

#define SDL_MAIN_HANDLED
#include <SDL.h>

#include <GL/glew.h>

#include <vector>

constexpr int8_t windowMouseDown = 1;
constexpr int8_t windowMouseUp = 2;
constexpr int8_t windowMoveUp = 3;
constexpr int8_t windowMoveDown = 4;
constexpr int8_t windowMoveRight = 5;
constexpr int8_t windowMoveLeft = 6;
constexpr int8_t windowExit = 128;

class Window {
    public:
        Window(int64_t sizeHorizontal, int64_t sizeVertical);
        ~Window();

        void init();
        void update();
        void setUiObjects(const std::vector<UiObject>& geometricObjects);
        int8_t getCurrentEvent();

    private:
        void updateEvent();
        void redraw();
        void drawObjects();
        void drawObject(const UiObject& geometricObject);

    private:
        SDL_Window* window = nullptr;
        std::vector<UiObject> uiObjects;
        int8_t currentEvent = 0;
};