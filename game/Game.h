#pragma once

#include <GameObject.h>

#include <vector>

constexpr size_t gameMoveUp = 1;
constexpr size_t gameMoveDown = 2;
constexpr size_t gameMoveTime = 3;
constexpr size_t gameMoveLeft = 4;
constexpr size_t gameMoveRight = 5;

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