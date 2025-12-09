#include <Game.hpp>

#include <GameObject.hpp>

void moveGameObjectUp(GameObject& gameObject) {
    static unsigned int topBorder = 50;
    static unsigned int stepSize = 1;

    unsigned int newVerticalPosition = gameObject.verticalPosition - stepSize;

    if (newVerticalPosition > topBorder) {
        gameObject.verticalPosition = newVerticalPosition;
    }
}

void moveGameObjectDown(GameObject& gameObject) {
    static unsigned int bottomBorder = 550;
    static unsigned int stepSize = 1;

    unsigned int newVerticalPosition = gameObject.verticalPosition + stepSize;

    if (newVerticalPosition + gameObject.verticalSize < bottomBorder) {
        gameObject.verticalPosition = newVerticalPosition;
    }
}

void moveGameObjectWithVelocity(GameObject& gameObject) {
    if (gameObject.horizontalVelocity == 0 && gameObject.verticalVelocity == 0) {
        return;
    }

    static unsigned int topBorder = 50;
    static unsigned int bottomBorder = 550;
    static unsigned int leftBorder = 50;
    static unsigned int rightBorder = 1150;

    static unsigned int stepSize = 1;

    unsigned int newHorizontal = gameObject.horizontalPosition + stepSize * gameObject.horizontalVelocity;

    if ((newHorizontal > leftBorder) && ((newHorizontal + gameObject.horizontalSize) < rightBorder)) {
        gameObject.horizontalPosition = newHorizontal;
    } else if (newHorizontal <= leftBorder) {
        gameObject.horizontalVelocity = -gameObject.horizontalVelocity;
        gameObject.horizontalPosition = leftBorder;
    } else if ((newHorizontal + gameObject.horizontalSize) >= rightBorder) {
        gameObject.horizontalVelocity = -gameObject.horizontalVelocity;
        gameObject.horizontalPosition = rightBorder - gameObject.horizontalSize;
    }

    unsigned int newVertical = gameObject.verticalPosition + stepSize * gameObject.verticalVelocity;

    if ((newVertical > topBorder) && ((newVertical + gameObject.verticalSize) < bottomBorder)) {
        gameObject.verticalPosition = newVertical;
    } else if (newVertical <= topBorder) {
        gameObject.verticalVelocity = -gameObject.verticalVelocity;
        gameObject.verticalPosition = topBorder;
    } else if ((newVertical + gameObject.verticalSize) >= bottomBorder) {
        gameObject.verticalVelocity = -gameObject.verticalVelocity;
        gameObject.verticalPosition = bottomBorder - gameObject.verticalSize;
    }
}

void updateGameObject(GameObject& gameObject, unsigned int gameEvent) {
    if (gameEvent == 0) {
        moveGameObjectWithVelocity(gameObject);
        return;
    }

    if (gameObject.horizontalVelocity != 0 || gameObject.verticalVelocity != 0) {
        return;
    }

    switch (gameEvent) {
        case MOVE_UP:
            moveGameObjectUp(gameObject);
            break;
        case MOVE_DOWN:
            moveGameObjectDown(gameObject);
            break;
    }
}

void Game::update() {
    for (GameObject& gameObject : gameObjects) {
        updateGameObject(gameObject, currentEvent);
    }
}

void Game::setCurrentEvent(unsigned int newEvent) {
    currentEvent = newEvent;
}

GameObject Game::getGameObject() {
    return gameObject;
}

std::vector<GameObject> Game::getGameObjects() {
    return gameObjects;
}