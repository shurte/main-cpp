#include <Converter.h>

#include <Controller.h>

std::shared_ptr<UiObject> Converter::getUiObject(const GameObject& gameObject) const {
    std::shared_ptr<UiObject> uiObject(new UiObject);
    uiObject->setData(0, ( (float) gameObject.horizontalPosition / WINDOW_SIZE_H) * 2.0f - 1.0f);
    uiObject->setData(1, (( (float) WINDOW_SIZE_V - gameObject.verticalPosition) / WINDOW_SIZE_V) * 2.0f - 1.0f);
    uiObject->setData(2, 0);

    uiObject->setData(3, (( (float) gameObject.horizontalPosition + gameObject.horizontalSize) / WINDOW_SIZE_H) * 2.0f - 1.0f);
    uiObject->setData(4, (( (float) WINDOW_SIZE_V - gameObject.verticalPosition) / WINDOW_SIZE_V) * 2.0f - 1.0f);
    uiObject->setData(5, 0);

    uiObject->setData(6, (( (float) gameObject.horizontalPosition + gameObject.horizontalSize) / WINDOW_SIZE_H) * 2.0f - 1.0f);
    uiObject->setData(7, (( (float) WINDOW_SIZE_V - gameObject.verticalPosition - gameObject.verticalSize) / WINDOW_SIZE_V) * 2.0f - 1.0f);
    uiObject->setData(8, 0);

    uiObject->setData(9, ( (float) gameObject.horizontalPosition / WINDOW_SIZE_H) * 2.0f - 1.0f);
    uiObject->setData(10, (( (float) WINDOW_SIZE_V - gameObject.verticalPosition - gameObject.verticalSize) / WINDOW_SIZE_V) * 2.0f - 1.0f);
    uiObject->setData(11, 0);

    return uiObject;
}

std::vector<std::shared_ptr<UiObject>> Converter::getUiObjects(const std::vector<GameObject>& gameObjects) const {
    std::vector<std::shared_ptr<UiObject>> uiObjects;
    uiObjects.reserve(gameObjects.size());

    for (const GameObject& gameObject : gameObjects) {
        std::shared_ptr<UiObject> geometricObject = getUiObject(gameObject);
        uiObjects.push_back(geometricObject);
    }

    return uiObjects;
}