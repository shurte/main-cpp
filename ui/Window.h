#pragma once

#include <UiObject.h>

#define SDL_MAIN_HANDLED
#include <SDL.h>

#include <GL/glew.h>

#include <memory>
#include <vector>

constexpr uint32_t windowMouseDown = 1;
constexpr uint32_t windowMouseUp = 2;
constexpr uint32_t windowMoveUp = 3;
constexpr uint32_t windowMoveDown = 4;
constexpr uint32_t windowMoveRight = 5;
constexpr uint32_t windowMoveLeft = 6;
constexpr uint32_t windowExit = 128;

class Window {
    public:
        Window(int64_t sizeHorizontal, int64_t sizeVertical);
        ~Window();

        void init();
        void update();
        void setUiObjects(const UiObjectPtrVector& geometricObjects);
        uint32_t getCurrentEvent();

    private:
        void updateEvent();
        void redraw();
        void drawObjects();
        void drawObject(UiObjectPtr uiObject);

    private:
        SDL_Window* window = nullptr;
        UiObjectPtrVector uiObjects;
        uint32_t currentEvent = 0;
};