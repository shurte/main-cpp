#include <Game.h>

#include <GameObject.h>

#include <memory>
#include <stdexcept>

void Game::moveGameObjectUp(std::shared_ptr<GameObject> gameObject) {
    static int topBorder = 50;
    static int stepSize = 1;

    int newVerticalPosition = gameObject->verticalPosition - stepSize;

    if (newVerticalPosition > topBorder) {
        gameObject->verticalPosition = newVerticalPosition;
    }
}

void Game::moveGameObjectDown(std::shared_ptr<GameObject> gameObject) {
    static int bottomBorder = 550;
    static int stepSize = 1;

    int newVerticalPosition = gameObject->verticalPosition + stepSize;

    if (newVerticalPosition + gameObject->verticalSize < bottomBorder) {
        gameObject->verticalPosition = newVerticalPosition;
    }
}

void Game::moveGameObjectLeft(std::shared_ptr<GameObject> gameObject) {
    static int leftBorder = 50;
    static int stepSize = 1;

    int newHorizontalPosition = gameObject->horizontalPosition - stepSize;

    if (newHorizontalPosition > leftBorder) {
        gameObject->horizontalPosition = newHorizontalPosition;
    }
}

void Game::moveGameObjectRight(std::shared_ptr<GameObject> gameObject) {
    static int rightBorder = 1150;
    static int stepSize = 1;

    int newHorizontalPosition = gameObject->horizontalPosition + stepSize;

    if (newHorizontalPosition + gameObject->horizontalSize < rightBorder) {
        gameObject->horizontalPosition = newHorizontalPosition;
    }
}

void Game::moveGameObjectWithVelocity(std::shared_ptr<GameObject> gameObject) {
    if (gameObject->horizontalVelocity == 0 && gameObject->verticalVelocity == 0) {
        return;
    }

    static int stepSize = 1;

    int topObject = gameObject->verticalPosition;
    int bottomObject = gameObject->verticalPosition + gameObject->verticalSize;
    int leftObject = gameObject->horizontalPosition;
    int rightObject = gameObject->horizontalPosition + gameObject->horizontalSize;
    
    int newTopObject = topObject + stepSize * gameObject->verticalVelocity;
    int newbottomObject = bottomObject + stepSize * gameObject->verticalVelocity;
    int newLeftObject = leftObject + stepSize * gameObject->horizontalVelocity;
    int newRightObject = rightObject + stepSize * gameObject->horizontalVelocity;

    bool isHorizontalChanged = false;
    bool isVerticalChanged = false;

    for (const std::shared_ptr<GameObject>& otherGameObject : getGameObjects()) {
        bool isTheSameObject = gameObject->horizontalPosition == otherGameObject->horizontalPosition
            && gameObject->verticalPosition == otherGameObject->verticalPosition
            && gameObject->verticalSize == otherGameObject->verticalSize
            && gameObject->horizontalSize == otherGameObject->horizontalSize;

        if (isTheSameObject) {
            continue;
        }

        int topBorder = otherGameObject->verticalPosition;
        int bottomBorder = otherGameObject->verticalPosition + otherGameObject->verticalSize;
        int rightBorder = otherGameObject->horizontalPosition + otherGameObject->horizontalSize;
        int leftBorder = otherGameObject->horizontalPosition;

        bool isVerticalAlignment 
            = topObject <= topBorder && bottomObject >= topBorder
            || topObject <= bottomBorder && bottomObject >= bottomBorder
            || topObject >= topBorder && topObject <= bottomBorder;

        bool isHorizontalAlignment 
            = leftObject <= leftBorder && rightObject >= leftBorder
            || leftObject <= rightBorder && rightObject >= rightBorder
            || leftObject >= leftBorder && leftObject <= rightBorder; 

        // check left collision
        if (isVerticalAlignment && (gameObject->horizontalVelocity < 0)) {
            if (leftObject >= rightBorder && newLeftObject < rightBorder && rightObject > rightBorder && !isHorizontalChanged) {
                isHorizontalChanged = true;
            }
        }

        // check right collision
        if (isVerticalAlignment && (gameObject->horizontalVelocity > 0)) {
            if (rightObject <= leftBorder && newRightObject > leftBorder && leftObject < leftBorder && !isHorizontalChanged) {
                isHorizontalChanged = true;
            }
        }

        // check top collision
        if (isHorizontalAlignment && gameObject->verticalVelocity < 0) {
            if (topObject >= bottomBorder && newTopObject < bottomBorder && bottomObject > bottomBorder && !isVerticalChanged) {
                isVerticalChanged = true;
            }
        }

        // check bottom collision
        if (isHorizontalAlignment && gameObject->verticalVelocity > 0) {
            if (bottomObject <= topBorder && newbottomObject > topBorder && topObject < topBorder && !isVerticalChanged) {
                isVerticalChanged = true;
            }
        }
    }

    if (isHorizontalChanged) {
        gameObject->horizontalVelocity = -gameObject->horizontalVelocity;
    }

    if (isVerticalChanged) {
        gameObject->verticalVelocity = -gameObject->verticalVelocity;
    }

    gameObject->horizontalPosition = gameObject->horizontalPosition + stepSize * gameObject->horizontalVelocity;
    gameObject->verticalPosition = gameObject->verticalPosition + stepSize * gameObject->verticalVelocity; 

    if (gameObject->horizontalPosition < 0 || gameObject->horizontalPosition > 1200 
        || gameObject->verticalPosition < 0 || gameObject->verticalPosition > 600 ) {
            throw std::runtime_error("Wrong position.");
        }
}

void Game::updateGameObject(std::shared_ptr<GameObject> gameObject, unsigned int gameEvent) {
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