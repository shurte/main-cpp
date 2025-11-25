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

void Controller::runLoop() {
    bool isRunning = true;

    while (isRunning) {
        window.setGeometricObjects(getGeometricObjects());
        window.update();
        size_t event = window.getCurrentEvent();

        if (event == WINDOW_EXIT) {
            isRunning = false;
        }
    }
}

void Controller::finish() {

}