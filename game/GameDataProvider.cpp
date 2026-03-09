#include <GameDataProvider.h>

std::vector<std::shared_ptr<GameObject>> GameDataProvider::getGameObjects() {
    std::vector<std::shared_ptr<GameObject>> gameObjects;

    std::shared_ptr<GameObject> gameRectangle(new GameObject);
    gameRectangle->horizontalPosition = 100;
    gameRectangle->verticalPosition = 100;
    gameRectangle->horizontalSize = 100;
    gameRectangle->verticalSize = 100;

    gameObjects.push_back(gameRectangle);

    std::shared_ptr<GameObject> gameRectangleWithVelocity(new GameObject);
    gameRectangleWithVelocity->horizontalPosition = 600;
    gameRectangleWithVelocity->verticalPosition = 100;
    gameRectangleWithVelocity->horizontalSize = 100;
    gameRectangleWithVelocity->verticalSize = 100;
    gameRectangleWithVelocity->horizontalVelocity = 10;
    gameRectangleWithVelocity->verticalVelocity = 10;

    gameObjects.push_back(gameRectangleWithVelocity);

    std::shared_ptr<GameObject> topBorder(new GameObject);
    topBorder->horizontalPosition = 0;
    topBorder->verticalPosition = 0;
    topBorder->horizontalSize = 1200;
    topBorder->verticalSize = 50;

    gameObjects.push_back(topBorder);

    std::shared_ptr<GameObject> bottomBorder(new GameObject);
    bottomBorder->horizontalPosition = 0;
    bottomBorder->verticalPosition = 550;
    bottomBorder->horizontalSize = 1200;
    bottomBorder->verticalSize = 50;

    gameObjects.push_back(bottomBorder);

    std::shared_ptr<GameObject> leftBorder(new GameObject);
    leftBorder->horizontalPosition = 0;
    leftBorder->verticalPosition = 0;
    leftBorder->horizontalSize = 50;
    leftBorder->verticalSize = 600;

    gameObjects.push_back(leftBorder);

    std::shared_ptr<GameObject> rightBorder(new GameObject);
    rightBorder->horizontalPosition = 1150;
    rightBorder->verticalPosition = 0;
    rightBorder->horizontalSize = 50;
    rightBorder->verticalSize = 600;

    gameObjects.push_back(rightBorder);

    return gameObjects;
}