#pragma once

#include <GameObject.hpp>

#include <vector>

#define MOVE_UP 1
#define MOVE_DOWN 2
#define MOVE_TIME 3

class Game {
    public:
        Game() {
        }

        void init();
        void update();
        void setCurrentEvent(unsigned int newEvent);
        std::vector<GameObject> getGameObjects();

    private:
        unsigned int currentEvent;
        std::vector<GameObject> gameObjects;
};