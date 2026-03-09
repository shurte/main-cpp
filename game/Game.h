#pragma once

#include <GameDataProvider.h>
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
        void moveGameObjectUp(std::shared_ptr<GameObject> gameObject);
        void moveGameObjectDown(std::shared_ptr<GameObject> gameObject);
        void moveGameObjectLeft(std::shared_ptr<GameObject> gameObject);
        void moveGameObjectRight(std::shared_ptr<GameObject> gameObject);
        void moveGameObjectWithVelocity(std::shared_ptr<GameObject> gameObject);
        void updateGameObject(std::shared_ptr<GameObject> gameObject, unsigned int gameEvent);

    private:
        unsigned int currentEvent;
        std::vector<std::shared_ptr<GameObject>> gameObjects;
        GameDataProvider gameDataProvider;
};