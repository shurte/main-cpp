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

    GeometricObject objectOne;
    objectOne.data = rectangle;
    objectOne.size = sizeof(rectangle);
    objectOne.vertexSize = 4;

    geometricObjects.push_back(objectOne);

    GeometricObject objectTwo;
    objectTwo.data = rectangleTwo;
    objectTwo.size = sizeof(rectangleTwo);
    objectTwo.vertexSize = 4;

    geometricObjects.push_back(objectTwo);

    GeometricObject objectThree;
    objectThree.data = triangle;
    objectThree.size = sizeof(triangle);
    objectThree.vertexSize = 3;

    geometricObjects.push_back(objectThree);

    return geometricObjects;
}

void Controller::init() {
    geometricObjects = getGeometricObjects();
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

void Controller::runLoop() {
    bool isRunning = true;

    window.setGeometricObjects(geometricObjects);
    window.drawScene();

    while (isRunning) {
        window.update();
        size_t event = window.getCurrentEvent();

        if (event == WINDOW_EXIT) {
            isRunning = false;
        } else if (event == WINDOW_MOVE_UP) {
            moveUpGeometricObject(geometricObjects[0]);
            // moveUp(rectangle, 4);
        } else if (event == WINDOW_MOVE_DOWN) {
            moveDown(rectangle, 4);
        }

        window.setGeometricObjects(geometricObjects);
        window.drawScene();
    }
}

void Controller::finish() {

}