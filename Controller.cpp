#include <Controller.hpp>

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

        milliseconds current = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
        while ((current - currentTime) < milliseconds(20)) {
            current = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
        }
        currentTime = current;

        game.update();
    }
}

void Controller::finish() {

}