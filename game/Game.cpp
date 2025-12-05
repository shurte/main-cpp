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

void updateGameObject(GameObject& gameObject, unsigned int gameEvent) {
    if (gameEvent == 0) return;

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
    updateGameObject(gameObject, currentEvent);
}

void Game::setCurrentEvent(unsigned int newEvent) {
    currentEvent = newEvent;
}

GameObject Game::getGameObject() {
    return gameObject;
}