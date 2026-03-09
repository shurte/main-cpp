#pragma once

#include <GameObject.h>

#include <memory>
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
        std::vector<std::shared_ptr<GameObject>> getGameObjects();

    private:
        unsigned int currentEvent;
        std::vector<std::shared_ptr<GameObject>> gameObjects;
};