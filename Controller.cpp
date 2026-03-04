#include <Controller.h>

#include <Hello.h>
#include <FrameManager.h>

#ifdef _WIN32
#include <wtypes.h>
#else
#include <limits.h>
#include <unistd.h>     //readlink
#endif

static FrameManager frameManager;
constexpr int64_t millisecondsInHalfFrame = 1000 / 120;
constexpr int64_t nanosecondsInHalfFrame = millisecondsInHalfFrame * 1000;

UiObject getUiObject(const GameObject& gameObject) {
    UiObject uiObject;
    uiObject.vertexSize = 4;
    uiObject.data = new float[4 * 3];
    uiObject.data[0] = ( (float) gameObject.horizontalPosition / WINDOW_SIZE_H) * 2.0f - 1.0f;
    uiObject.data[1] = (( (float) WINDOW_SIZE_V - gameObject.verticalPosition) / WINDOW_SIZE_V) * 2.0f - 1.0f;
    uiObject.data[2] = 0;

    uiObject.data[3] = (( (float) gameObject.horizontalPosition + gameObject.horizontalSize) / WINDOW_SIZE_H) * 2.0f - 1.0f;
    uiObject.data[4] = (( (float) WINDOW_SIZE_V - gameObject.verticalPosition) / WINDOW_SIZE_V) * 2.0f - 1.0f;
    uiObject.data[5] = 0;

    uiObject.data[6] = (( (float) gameObject.horizontalPosition + gameObject.horizontalSize) / WINDOW_SIZE_H) * 2.0f - 1.0f;
    uiObject.data[7] = (( (float) WINDOW_SIZE_V - gameObject.verticalPosition - gameObject.verticalSize) / WINDOW_SIZE_V) * 2.0f - 1.0f;
    uiObject.data[8] = 0;

    uiObject.data[9] = ( (float) gameObject.horizontalPosition / WINDOW_SIZE_H) * 2.0f - 1.0f;
    uiObject.data[10] = (( (float) WINDOW_SIZE_V - gameObject.verticalPosition - gameObject.verticalSize) / WINDOW_SIZE_V) * 2.0f - 1.0f;
    uiObject.data[11] = 0;

    return uiObject;
}

std::vector<UiObject> getUiObjects(const std::vector<GameObject>& gameObjects) {
    std::vector<UiObject> uiObjects(gameObjects.size());

    for (const GameObject& gameObject : gameObjects) {
        UiObject geometricObject = getUiObject(gameObject);
        uiObjects.push_back(geometricObject);
    }

    return uiObjects;
}

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

        size_t event = window.getCurrentEvent();

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
    window.setUiObjects(getUiObjects(gameObjects));
    window.update();
}

void sleep() {
    #ifdef _WIN32
    Sleep(millisecondsInHalfFrame);
    #else
    timespec mySpec, myRem;
    mySpec.tv_nsec = nanosecondsInHalfFrame;
    nanosleep(&mySpec, &myRem);
    #endif
}

void Controller::updateGame() {
    int64_t startFrames = frameManager.getFramesFromStart();
    game.update();
    int64_t currentFrames = frameManager.getFramesFromStart();

    while (currentFrames - startFrames < 1) {
        sleep();
        currentFrames = frameManager.getFramesFromStart();
    }

    ++startFrames;

    while (currentFrames > startFrames) {
        game.update();
        ++startFrames;
    }
}