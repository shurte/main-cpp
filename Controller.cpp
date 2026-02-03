#include <Controller.hpp>

#include <FrameManager.hpp>

#ifdef _WIN32
#include <wtypes.h>
#else
#include <limits.h>
#include <unistd.h>     //readlink
#endif

static FrameManager frameManager;
constexpr int64_t millisecondsInHalfFrame = 1000 / 120;
constexpr int64_t nanosecondsInHalfFrame = millisecondsInHalfFrame * 1000;

GeometricObject getGeometricObject(const GameObject& gameObject) {
    GeometricObject geometricObject;
    geometricObject.vertexSize = 4;
    geometricObject.data = new float[4 * 3];
    geometricObject.data[0] = ( (float) gameObject.horizontalPosition / WINDOW_SIZE_H) * 2.0f - 1.0f;
    geometricObject.data[1] = (( (float) WINDOW_SIZE_V - gameObject.verticalPosition) / WINDOW_SIZE_V) * 2.0f - 1.0f;
    geometricObject.data[2] = 0;

    geometricObject.data[3] = (( (float) gameObject.horizontalPosition + gameObject.horizontalSize) / WINDOW_SIZE_H) * 2.0f - 1.0f;
    geometricObject.data[4] = (( (float) WINDOW_SIZE_V - gameObject.verticalPosition) / WINDOW_SIZE_V) * 2.0f - 1.0f;
    geometricObject.data[5] = 0;

    geometricObject.data[6] = (( (float) gameObject.horizontalPosition + gameObject.horizontalSize) / WINDOW_SIZE_H) * 2.0f - 1.0f;
    geometricObject.data[7] = (( (float) WINDOW_SIZE_V - gameObject.verticalPosition - gameObject.verticalSize) / WINDOW_SIZE_V) * 2.0f - 1.0f;
    geometricObject.data[8] = 0;

    geometricObject.data[9] = ( (float) gameObject.horizontalPosition / WINDOW_SIZE_H) * 2.0f - 1.0f;
    geometricObject.data[10] = (( (float) WINDOW_SIZE_V - gameObject.verticalPosition - gameObject.verticalSize) / WINDOW_SIZE_V) * 2.0f - 1.0f;
    geometricObject.data[11] = 0;

    return geometricObject;
}

void Controller::init() {
    game.init();
    window.init();
    frameManager.start();
}

void Controller::runLoop() {
    bool isRunning = true;

    while (isRunning) {
        geometricObjects.clear();
        std::vector<GameObject> gameObjects = game.getGameObjects();

        for (const GameObject& gameObject : gameObjects) {
            GeometricObject geometricObject = getGeometricObject(gameObject);
            geometricObjects.push_back(geometricObject);
        }

        window.setGeometricObjects(geometricObjects);
        window.update();
        int64_t startFrames = frameManager.getFramesFromStart();
        size_t event = window.getCurrentEvent();

        if (event == WINDOW_EXIT) {
            isRunning = false;
        } else if (event == WINDOW_MOVE_UP) {
            game.setCurrentEvent(MOVE_UP);
        } else if (event == WINDOW_MOVE_DOWN) {
            game.setCurrentEvent(MOVE_DOWN);
        } else {
            game.setCurrentEvent(0);
        }

        timespec mySpec, myRem;
        mySpec.tv_nsec = nanosecondsInHalfFrame;
        game.update();
        int64_t currentFrames = frameManager.getFramesFromStart();

        while (currentFrames - startFrames < 1) {
            #ifdef _WIN32
            Sleep(millisecondsInHalfFrame);
            #else
            nanosleep(&mySpec, &myRem);
            #endif
            currentFrames = frameManager.getFramesFromStart();
        }

        ++startFrames;

        while (currentFrames > startFrames) {
            game.update();
            ++startFrames;
        }
    }
}

void Controller::finish() {

}