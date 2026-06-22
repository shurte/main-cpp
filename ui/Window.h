#pragma once

#include <UiObject.h>

#define SDL_MAIN_HANDLED
#include <SDL.h>

#include <GL/glew.h>

#include <memory>
#include <vector>

constexpr unsigned windowMouseDown = 1;
constexpr unsigned windowMouseUp = 2;
constexpr unsigned windowMoveUp = 3;
constexpr unsigned windowMoveDown = 4;
constexpr unsigned windowMoveRight = 5;
constexpr unsigned windowMoveLeft = 6;
constexpr unsigned windowExit = 128;

class Window {
    public:
        Window(int64_t sizeHorizontal, int64_t sizeVertical);
        ~Window();

        void init();
        void update();
        void setUiObjects(const UiObjectPtrVector& geometricObjects);
        unsigned getCurrentEvent();

    private:
        void updateEvent();
        void redraw();
        void drawObjects();
        void drawObject(UiObjectPtr uiObject);

    private:
        SDL_Window* window = nullptr;
        UiObjectPtrVector uiObjects;
        unsigned currentEvent = 0;
};