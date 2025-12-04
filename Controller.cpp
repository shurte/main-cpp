#include <Controller.hpp>

static float rectangle[] = {
    -0.25f, 0.75f, 0.0f,
    -0.25f, 0.25f, 0.0f,
    -0.75f, 0.25f, 0.0f,
    -0.75f, 0.75f, 0.0f,
};

static float rectangleTwo[] = {
    0.25f, 0.75f, 0.0f,
    0.25f, 0.25f, 0.0f,
    0.75f, 0.25f, 0.0f,
    0.75f, 0.75f, 0.0f,
};

static float triangle[] = {
    0.5f, -0.25f, 0.0f,
    0.25f, -0.75f, 0.0f,
    0.75f, -0.75f, 0.0f
};

std::vector<GeometricObject> Controller::getGeometricObjects() {
    std::vector<GeometricObject> geometricObjects;

    // GeometricObject objectOne;
    // objectOne.data = rectangle;
    // objectOne.vertexSize = 4;

    // geometricObjects.push_back(objectOne);

    GeometricObject objectTwo;
    objectTwo.data = rectangleTwo;
    objectTwo.vertexSize = 4;

    geometricObjects.push_back(objectTwo);

    GeometricObject objectThree;
    objectThree.data = triangle;
    objectThree.vertexSize = 3;

    geometricObjects.push_back(objectThree);

    return geometricObjects;
}

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
    // geometricObjects = getGeometricObjects();

    GameObject gameRectangle;
    gameRectangle.horizontalPosition = 100;
    gameRectangle.verticalPosition = 100;
    gameRectangle.horizontalSize = 100;
    gameRectangle.verticalSize = 100;

    gameObjects.push_back(gameRectangle);
    GeometricObject aloneGeometricObject = getGeometricObject(gameRectangle);

    geometricObjects.push_back(aloneGeometricObject);

    window.initGraphicArrayAndBuffer();
}

void moveUp(float *data, size_t size) {
    float topBorder = -1.0f;

    for (size_t i = 0; i < size; ++i) {
        size_t index = i * 3 + 1;
        if ((data[index]) > topBorder) {
            topBorder = data[index];
        }
    }

    if ((topBorder + 0.1f) > 1.0f) {
        return;
    }

    for (size_t i = 0; i < size; ++i) {
        size_t index = i * 3 + 1;
        int cache = round(data[index] * 100);
        int newValue = cache + 1;
        data[index] = (float) newValue / 100.0f;
    }
}

void moveUpGeometricObject(GeometricObject& geometricObject) {
    moveUp(geometricObject.data, geometricObject.vertexSize);
}

void moveDown(float *data, size_t size) {
    float bottomBorder = 1.0f;

    for (size_t i = 0; i < size; ++i) {
        size_t index = i * 3 + 1;
        if ((data[index]) < bottomBorder) {
            bottomBorder = data[index];
        }
    }

    if ((bottomBorder - 0.1f) < -1.0f) {
        return;
    }

    for (size_t i = 0; i < size; ++i) {
        size_t index = i * 3 + 1;
        int cache = round(data[index] * 100);
        int newValue = cache - 1;
        data[index] = (float) newValue / 100.0f;
    }
}

void moveDownGeometricObject(GeometricObject& geometricObject) {
    moveDown(geometricObject.data, geometricObject.vertexSize);
}

void Controller::runLoop() {
    bool isRunning = true;

    while (isRunning) {
        window.setGeometricObjects(geometricObjects);
        window.drawScene();
        window.update();

        size_t event = window.getCurrentEvent();

        if (event == WINDOW_EXIT) {
            isRunning = false;
        } else if (event == WINDOW_MOVE_UP) {
            moveUpGeometricObject(geometricObjects[0]);
        } else if (event == WINDOW_MOVE_DOWN) {
            moveDownGeometricObject(geometricObjects[0]);
        }
    }
}

void Controller::finish() {

}