#pragma once

#include <GameObject.hpp>

#define MOVE_UP 1
#define MOVE_DOWN 2

class Game {
    public:
        Game() {
            gameObject.horizontalPosition = 100;
            gameObject.verticalPosition = 100;
            gameObject.horizontalSize = 100;
            gameObject.verticalSize = 100;
        }
        void update();
        void setCurrentEvent(unsigned int newEvent);
        GameObject getGameObject();
    private:
        unsigned int currentEvent;
        GameObject gameObject;
};