#include <Game.h>

#include <GameObject.h>

#include <memory>

void moveGameObjectUp(std::shared_ptr<GameObject> gameObject) {
    static unsigned int topBorder = 50;
    static unsigned int stepSize = 1;

    unsigned int newVerticalPosition = gameObject->verticalPosition - stepSize;

    if (newVerticalPosition > topBorder) {
        gameObject->verticalPosition = newVerticalPosition;
    }
}

void moveGameObjectDown(std::shared_ptr<GameObject> gameObject) {
    static unsigned int bottomBorder = 550;
    static unsigned int stepSize = 1;

    unsigned int newVerticalPosition = gameObject->verticalPosition + stepSize;

    if (newVerticalPosition + gameObject->verticalSize < bottomBorder) {
        gameObject->verticalPosition = newVerticalPosition;
    }
}

void moveGameObjectLeft(std::shared_ptr<GameObject> gameObject) {
    static unsigned int leftBorder = 50;
    static unsigned int stepSize = 1;

    unsigned int newHorizontalPosition = gameObject->horizontalPosition - stepSize;

    if (newHorizontalPosition > leftBorder) {
        gameObject->horizontalPosition = newHorizontalPosition;
    }
}

void moveGameObjectRight(std::shared_ptr<GameObject> gameObject) {
    static unsigned int rightBorder = 1150;
    static unsigned int stepSize = 1;

    unsigned int newHorizontalPosition = gameObject->horizontalPosition + stepSize;

    if (newHorizontalPosition + gameObject->horizontalSize < rightBorder) {
        gameObject->horizontalPosition = newHorizontalPosition;
    }
}

void moveGameObjectWithVelocity(std::shared_ptr<GameObject> gameObject) {
    if (gameObject->horizontalVelocity == 0 && gameObject->verticalVelocity == 0) {
        return;
    }

    static unsigned int topBorder = 50;
    static unsigned int bottomBorder = 550;
    static unsigned int leftBorder = 50;
    static unsigned int rightBorder = 1150;

    static unsigned int stepSize = 1;

    unsigned int newHorizontal = gameObject->horizontalPosition + stepSize * gameObject->horizontalVelocity;

    if ((newHorizontal > leftBorder) && ((newHorizontal + gameObject->horizontalSize) < rightBorder)) {
        gameObject->horizontalPosition = newHorizontal;
    } else if (newHorizontal <= leftBorder) {
        gameObject->horizontalVelocity = -gameObject->horizontalVelocity;
        gameObject->horizontalPosition = leftBorder;
    } else if ((newHorizontal + gameObject->horizontalSize) >= rightBorder) {
        gameObject->horizontalVelocity = -gameObject->horizontalVelocity;
        gameObject->horizontalPosition = rightBorder - gameObject->horizontalSize;
    }

    unsigned int newVertical = gameObject->verticalPosition + stepSize * gameObject->verticalVelocity;

    if ((newVertical > topBorder) && ((newVertical + gameObject->verticalSize) < bottomBorder)) {
        gameObject->verticalPosition = newVertical;
    } else if (newVertical <= topBorder) {
        gameObject->verticalVelocity = -gameObject->verticalVelocity;
        gameObject->verticalPosition = topBorder;
    } else if ((newVertical + gameObject->verticalSize) >= bottomBorder) {
        gameObject->verticalVelocity = -gameObject->verticalVelocity;
        gameObject->verticalPosition = bottomBorder - gameObject->verticalSize;
    }
}

void updateGameObject(std::shared_ptr<GameObject> gameObject, unsigned int gameEvent) {
    if (gameObject->horizontalVelocity != 0 || gameObject->verticalVelocity != 0) {
        moveGameObjectWithVelocity(gameObject);
        return;
    }

    if ((gameObject->horizontalSize == 100) && (gameObject->verticalSize == 100)) {
        switch (gameEvent) {
            case gameMoveUp:
                moveGameObjectUp(gameObject);
                break;
            case gameMoveDown:
                moveGameObjectDown(gameObject);
                break;
            case gameMoveLeft:
                moveGameObjectLeft(gameObject);
                break;
            case gameMoveRight:
                moveGameObjectRight(gameObject);
                break;
        }

        return;
    }
}

void Game::init() {
    std::vector<std::shared_ptr<GameObject>> gameObjects = gameDataProvider.getGameObjects();
    this->gameObjects = gameObjects;
}

void Game::update() {
    for (std::shared_ptr<GameObject> gameObject : gameObjects) {
        updateGameObject(gameObject, currentEvent);
    }
}

void Game::setCurrentEvent(size_t newEvent) {
    currentEvent = newEvent;
}

std::vector<std::shared_ptr<GameObject>> Game::getGameObjects() {
    return gameObjects;
}