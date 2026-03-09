#pragma once

#include <UiObject.h>

#define SDL_MAIN_HANDLED
#include <SDL.h>

#include <GL/glew.h>

#include <memory>
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
        void setUiObjects(const UiObjectPtrVector& geometricObjects);
        int8_t getCurrentEvent();

    private:
        void updateEvent();
        void redraw();
        void drawObjects();
        void drawObject(UiObjectPtr uiObject);

    private:
        SDL_Window* window = nullptr;
        UiObjectPtrVector uiObjects;
        int8_t currentEvent = 0;
};