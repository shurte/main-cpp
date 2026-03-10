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

    static int topBorder = 50;
    static int bottomBorder = 550;
    static int leftBorder = 50;
    static int rightBorder = 1150;

    static int stepSize = 1;

    int newHorizontal = gameObject->horizontalPosition + stepSize * gameObject->horizontalVelocity;
    int newVertical = gameObject->verticalPosition + stepSize * gameObject->verticalVelocity;

    bool isHorizontalChanged = false;
    bool isVerticalChanged = false;

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
            = (gameObject->verticalPosition >= otherGameObject->verticalPosition && gameObject->verticalPosition <= (otherGameObject->verticalPosition + otherGameObject->verticalSize))
            || ((gameObject->verticalPosition + gameObject->verticalSize) >= otherGameObject->verticalPosition && (gameObject->verticalPosition + gameObject->verticalSize) <= (otherGameObject->verticalPosition + otherGameObject->verticalSize))
            || (gameObject->verticalPosition <= otherGameObject->verticalPosition && (gameObject->verticalPosition + gameObject->verticalSize) >= otherGameObject->verticalPosition)
            || (gameObject->verticalPosition <= (otherGameObject->verticalPosition + otherGameObject->verticalSize) && (gameObject->verticalPosition + gameObject->verticalSize) >= (otherGameObject->verticalPosition + otherGameObject->verticalSize)); 

        bool isHorizontalAlignment 
            = (gameObject->horizontalPosition >= otherGameObject->horizontalPosition && gameObject->horizontalPosition <= otherGameObject->horizontalPosition + otherGameObject->horizontalSize)
            || ((gameObject->horizontalPosition + gameObject->horizontalSize) >= otherGameObject->horizontalPosition && (gameObject->horizontalPosition + gameObject->horizontalSize) <= (otherGameObject->horizontalPosition + otherGameObject->horizontalSize))
            || (gameObject->horizontalPosition <= otherGameObject->horizontalPosition && (gameObject->horizontalPosition + gameObject->horizontalSize) >= otherGameObject->horizontalPosition)
            || (gameObject->horizontalPosition <= (otherGameObject->horizontalPosition + otherGameObject->horizontalSize) && (gameObject->horizontalPosition + gameObject->horizontalSize) >= (otherGameObject->horizontalPosition + otherGameObject->horizontalSize)); 

        // check left collision
        if (isVerticalAlignment && (gameObject->horizontalVelocity < 0)) {
            if (newHorizontal > rightBorder) {
                // gameObject->horizontalPosition = newHorizontal;
            } else if ((newHorizontal <= rightBorder) && ((newHorizontal + gameObject->horizontalSize) > rightBorder) && !isHorizontalChanged) {
                gameObject->horizontalVelocity = -gameObject->horizontalVelocity;
                newHorizontal = rightBorder;
                isHorizontalChanged = true;
            }
        }

        // check right collision
        if (isVerticalAlignment && (gameObject->horizontalVelocity > 0)) {
            if (newHorizontal + gameObject->horizontalSize < leftBorder) {
                // newHorizontal = newHorizontal;
            } else if ((newHorizontal + gameObject->horizontalSize >= leftBorder) && (newHorizontal < leftBorder) && !isHorizontalChanged) {
                gameObject->horizontalVelocity = -gameObject->horizontalVelocity;
                newHorizontal = leftBorder - gameObject->horizontalSize;
                isHorizontalChanged = true;
            }
        }

        // check top collision
        if (isHorizontalAlignment && gameObject->verticalVelocity < 0) {
            if (newVertical < bottomBorder) {
                // gameObject->verticalPosition = newVertical;
            } else if ((newVertical <= bottomBorder) && (newVertical + gameObject->verticalSize > bottomBorder) && !isVerticalChanged) {
                gameObject->verticalVelocity = -gameObject->verticalVelocity;
                newVertical = bottomBorder;
                isVerticalChanged = true;
            }
        }

        // check bottom collision
        if (isHorizontalAlignment && gameObject->verticalVelocity > 0) {
            if (newVertical + gameObject->verticalSize < topBorder) {
                // gameObject->verticalPosition = newVertical;
            } else if ((newVertical + gameObject->verticalSize >= topBorder) && (newVertical < topBorder) && !isVerticalChanged) {
                gameObject->verticalVelocity = -gameObject->verticalVelocity;
                newVertical = topBorder - gameObject->verticalSize;
                isVerticalChanged = true;
            }
        }
    }

    gameObject->horizontalPosition = newHorizontal;
    gameObject->verticalPosition = newVertical;

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