#include <Converter.h>

#include <Controller.h>

UiObjectPtr Converter::getUiObject(const GameObject& gameObject) const {
    UiObjectPtr uiObject(new UiObject);
    uiObject->setXValue(0, ( (float) gameObject.horizontalPosition / WINDOW_SIZE_H) * 2.0f - 1.0f);
    uiObject->setYValue(0, (( (float) WINDOW_SIZE_V - gameObject.verticalPosition) / WINDOW_SIZE_V) * 2.0f - 1.0f);
    uiObject->setZValue(0, 0);

    uiObject->setXValue(1, (( (float) gameObject.horizontalPosition + gameObject.horizontalSize) / WINDOW_SIZE_H) * 2.0f - 1.0f);
    uiObject->setYValue(1, (( (float) WINDOW_SIZE_V - gameObject.verticalPosition) / WINDOW_SIZE_V) * 2.0f - 1.0f);
    uiObject->setZValue(1, 0);

    uiObject->setXValue(2, (( (float) gameObject.horizontalPosition + gameObject.horizontalSize) / WINDOW_SIZE_H) * 2.0f - 1.0f);
    uiObject->setYValue(2, (( (float) WINDOW_SIZE_V - gameObject.verticalPosition - gameObject.verticalSize) / WINDOW_SIZE_V) * 2.0f - 1.0f);
    uiObject->setZValue(2, 0);

    uiObject->setXValue(3, ( (float) gameObject.horizontalPosition / WINDOW_SIZE_H) * 2.0f - 1.0f);
    uiObject->setYValue(3, (( (float) WINDOW_SIZE_V - gameObject.verticalPosition - gameObject.verticalSize) / WINDOW_SIZE_V) * 2.0f - 1.0f);
    uiObject->setZValue(3, 0);

    return uiObject;
}

UiObjectPtrVector Converter::getUiObjects(const std::vector<GameObject>& gameObjects) const {
    UiObjectPtrVector uiObjects;
    uiObjects.reserve(gameObjects.size());

    for (const GameObject& gameObject : gameObjects) {
        UiObjectPtr geometricObject = getUiObject(gameObject);
        uiObjects.push_back(geometricObject);
    }

    return uiObjects;
}