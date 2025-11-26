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
    window.initObjects();
    window.setGeometricObjects(getGeometricObjects());
}

void moveUp(float *data, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        size_t index = i * 3 + 1;
        int cache = data[index] * 100;
        int newValue = cache + 10;
        if (newValue > 100) newValue = rectangleTwo[index] * 100;
        data[index] = (float) newValue / 100.0f;
    }
}

void Controller::runLoop() {
    bool isRunning = true;

    window.setGeometricObjects(getGeometricObjects());
    window.drawScene();

    while (isRunning) {
        window.update();
        size_t event = window.getCurrentEvent();

        if (event == WINDOW_EXIT) {
            isRunning = false;
        } else if (event == WINDOW_MOUSE_UP) {
            moveUp(rectangle, 4);
        }

        window.setGeometricObjects(getGeometricObjects());
        window.drawScene();
    }
}

void Controller::finish() {

}