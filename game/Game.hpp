#pragma once

#include <GameObject.hpp>

#include <vector>

#define MOVE_UP 1
#define MOVE_DOWN 2
#define MOVE_TIME 3

class Game {
    public:
        Game() {
            gameObject.horizontalPosition = 100;
            gameObject.verticalPosition = 100;
            gameObject.horizontalSize = 100;
            gameObject.verticalSize = 100;

            GameObject gameRectangle;
            gameRectangle.horizontalPosition = 100;
            gameRectangle.verticalPosition = 100;
            gameRectangle.horizontalSize = 100;
            gameRectangle.verticalSize = 100;

            gameObjects.push_back(gameRectangle);

            GameObject gameRectangleWithVelocity;
            gameRectangleWithVelocity.horizontalPosition = 600;
            gameRectangleWithVelocity.verticalPosition = 100;
            gameRectangleWithVelocity.horizontalSize = 100;
            gameRectangleWithVelocity.verticalSize = 100;
            gameRectangleWithVelocity.horizontalVelocity = 10;
            gameRectangleWithVelocity.verticalVelocity = 10;

            gameObjects.push_back(gameRectangleWithVelocity);
        }

        void update();
        void setCurrentEvent(unsigned int newEvent);
        GameObject getGameObject();
        std::vector<GameObject> getGameObjects();

    private:
        unsigned int currentEvent;
        GameObject gameObject;
        std::vector<GameObject> gameObjects;
};