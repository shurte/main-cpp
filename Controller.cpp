#include <Controller.h>

#include <Hello.h>

constexpr uint64_t millisecondsInHalfFrame = 1000 / 120;

void Controller::init() {
    hello::clock();
    std::string directory = hello::getAppDirectory();
    hello::write(directory);

    game.init();
    window.init();
    frameManager.start();
}

void Controller::runLoop() {
    bool isRunning = true;

    while (isRunning) {
        updateWindow();

        int8_t event = window.getCurrentEvent();

        if (event == windowExit) {
            isRunning = false;
        } else if (event == windowMoveUp) {
            game.setCurrentEvent(MOVE_UP);
        } else if (event == windowMoveDown) {
            game.setCurrentEvent(MOVE_DOWN);
        } else if (event == windowMoveLeft) {
            game.setCurrentEvent(MOVE_LEFT);
        } else if (event == windowMoveRight) {
            game.setCurrentEvent(MOVE_RIGHT);
        } else {
            game.setCurrentEvent(0);
        }

        updateGame();
    }
}

void Controller::finish() {

}

void Controller::updateWindow() {
    const std::vector<GameObject>& gameObjects = game.getGameObjects();
    window.setUiObjects(converter.getUiObjects(gameObjects));
    window.update();
}

void Controller::updateGame() {
    int64_t startFrames = frameManager.getFramesFromStart();
    game.update();
    int64_t currentFrames = frameManager.getFramesFromStart();

    while (currentFrames - startFrames < 1) {
        hello::sleep(millisecondsInHalfFrame);
        currentFrames = frameManager.getFramesFromStart();
    }

    ++startFrames;

    while (currentFrames > startFrames) {
        game.update();
        ++startFrames;
    }
}