#include <Game.h>

#include <GameObject.h>

#include <memory>

void Game::moveGameObjectUp(std::shared_ptr<GameObject> gameObject) {
    static unsigned int topBorder = 50;
    static unsigned int stepSize = 1;

    unsigned int newVerticalPosition = gameObject->verticalPosition - stepSize;

    if (newVerticalPosition > topBorder) {
        gameObject->verticalPosition = newVerticalPosition;
    }
}

void Game::moveGameObjectDown(std::shared_ptr<GameObject> gameObject) {
    static unsigned int bottomBorder = 550;
    static unsigned int stepSize = 1;

    unsigned int newVerticalPosition = gameObject->verticalPosition + stepSize;

    if (newVerticalPosition + gameObject->verticalSize < bottomBorder) {
        gameObject->verticalPosition = newVerticalPosition;
    }
}

void Game::moveGameObjectLeft(std::shared_ptr<GameObject> gameObject) {
    static unsigned int leftBorder = 50;
    static unsigned int stepSize = 1;

    unsigned int newHorizontalPosition = gameObject->horizontalPosition - stepSize;

    if (newHorizontalPosition > leftBorder) {
        gameObject->horizontalPosition = newHorizontalPosition;
    }
}

void Game::moveGameObjectRight(std::shared_ptr<GameObject> gameObject) {
    static unsigned int rightBorder = 1150;
    static unsigned int stepSize = 1;

    unsigned int newHorizontalPosition = gameObject->horizontalPosition + stepSize;

    if (newHorizontalPosition + gameObject->horizontalSize < rightBorder) {
        gameObject->horizontalPosition = newHorizontalPosition;
    }
}

void Game::moveGameObjectWithVelocity(std::shared_ptr<GameObject> gameObject) {
    if (gameObject->horizontalVelocity == 0 && gameObject->verticalVelocity == 0) {
        return;
    }

    static unsigned int topBorder = 50;
    static unsigned int bottomBorder = 550;
    static unsigned int leftBorder = 50;
    static unsigned int rightBorder = 1150;

    static unsigned int stepSize = 1;

    unsigned int newHorizontal = gameObject->horizontalPosition + stepSize * gameObject->horizontalVelocity;
    unsigned int newVertical = gameObject->verticalPosition + stepSize * gameObject->verticalVelocity;

    for (const std::shared_ptr<GameObject>& otherGameObject : getGameObjects()) {
        if (gameObject->horizontalPosition == otherGameObject->horizontalPosition
            && gameObject->verticalPosition == otherGameObject->verticalPosition
            && gameObject->verticalSize == otherGameObject->verticalSize
            && gameObject->horizontalSize == otherGameObject->horizontalSize) {
                continue;
        }

        topBorder = otherGameObject->verticalPosition;
        bottomBorder = otherGameObject->verticalPosition + otherGameObject->verticalSize;
        rightBorder = otherGameObject->horizontalPosition + otherGameObject->horizontalSize;
        leftBorder = otherGameObject->horizontalPosition;

        bool isVerticalAlignment 
            = (gameObject->verticalPosition >= otherGameObject->verticalPosition && (gameObject->verticalPosition + gameObject->verticalSize) > otherGameObject->verticalPosition)
            || (gameObject->verticalPosition <= (otherGameObject->verticalPosition + otherGameObject->verticalSize) && (gameObject->verticalPosition + gameObject->verticalSize) > (otherGameObject->verticalPosition + otherGameObject->verticalSize)); 

        bool isHorizontalAlignment 
            = (gameObject->horizontalPosition >= otherGameObject->horizontalPosition && gameObject->horizontalPosition <= otherGameObject->horizontalPosition + otherGameObject->horizontalSize)
            || ((gameObject->horizontalPosition + gameObject->horizontalSize) >= otherGameObject->horizontalPosition && (gameObject->horizontalPosition + gameObject->horizontalSize) <= (otherGameObject->horizontalPosition + otherGameObject->horizontalSize))
            || (gameObject->horizontalPosition <= otherGameObject->horizontalPosition && (gameObject->horizontalPosition + gameObject->horizontalSize) >= otherGameObject->horizontalPosition)
            || (gameObject->horizontalPosition <= (otherGameObject->horizontalPosition + otherGameObject->horizontalSize) && (gameObject->horizontalPosition + gameObject->horizontalSize) >= (otherGameObject->horizontalPosition + otherGameObject->horizontalSize)); 

        // check left collision
        if (isVerticalAlignment && (gameObject->horizontalVelocity < 0)) {
            if (newHorizontal > rightBorder) {
                // gameObject->horizontalPosition = newHorizontal;
            } else if ((newHorizontal <= rightBorder) && ((newHorizontal + gameObject->horizontalSize) > rightBorder)) {
                gameObject->horizontalVelocity = -gameObject->horizontalVelocity;
                newHorizontal = rightBorder;
            }
        }

        // check right collision
        if (isVerticalAlignment && (gameObject->horizontalVelocity > 0)) {
            if (newHorizontal + gameObject->horizontalSize < leftBorder) {
                // newHorizontal = newHorizontal;
            } else if ((newHorizontal + gameObject->horizontalSize >= leftBorder) && (newHorizontal < leftBorder)) {
                gameObject->horizontalVelocity = -gameObject->horizontalVelocity;
                newHorizontal = leftBorder - gameObject->horizontalSize;
            }
        }

        // check top collision
        if (isHorizontalAlignment && gameObject->verticalVelocity < 0) {
            if (newVertical < bottomBorder) {
                // gameObject->verticalPosition = newVertical;
            } else if ((newVertical <= bottomBorder) && (newVertical + gameObject->verticalSize > bottomBorder)) {
                gameObject->verticalVelocity = -gameObject->verticalVelocity;
                newVertical = bottomBorder;
            }
        }

        // check bottom collision
        if (isHorizontalAlignment && gameObject->verticalVelocity > 0) {
            if (newVertical + gameObject->verticalSize < topBorder) {
                // gameObject->verticalPosition = newVertical;
            } else if ((newVertical + gameObject->verticalSize >= topBorder) && (newVertical < topBorder)) {
                gameObject->verticalVelocity = -gameObject->verticalVelocity;
                newVertical = topBorder - gameObject->verticalSize;
            }
        }
    }

    gameObject->horizontalPosition = newHorizontal;
    gameObject->verticalPosition = newVertical;
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