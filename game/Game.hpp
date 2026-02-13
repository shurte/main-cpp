#pragma once

#include <GameObject.hpp>

#include <vector>

constexpr size_t MOVE_UP = 1;
constexpr size_t MOVE_DOWN = 2;
constexpr size_t MOVE_TIME = 3;
constexpr size_t MOVE_LEFT = 4;
constexpr size_t MOVE_RIGHT = 5;

class Game {
    public:
        Game() {
        }

        void init();
        void update();
        void setCurrentEvent(size_t newEvent);
        std::vector<GameObject> getGameObjects();

    private:
        unsigned int currentEvent;
        std::vector<GameObject> gameObjects;
};