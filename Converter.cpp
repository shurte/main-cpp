#include <Converter.h>

#include <Controller.h>

UiObject Converter::getUiObject(const GameObject& gameObject) const {
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

std::vector<UiObject> Converter::getUiObjects(const std::vector<GameObject>& gameObjects) const {
    std::vector<UiObject> uiObjects(gameObjects.size());

    for (const GameObject& gameObject : gameObjects) {
        UiObject geometricObject = getUiObject(gameObject);
        uiObjects.push_back(geometricObject);
    }

    return uiObjects;
}