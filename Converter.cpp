#include <Converter.h>

#include <Controller.h>

constexpr unsigned HorizontalStart = 0;
constexpr unsigned HorizontalEnd = WINDOW_SIZE_H;
constexpr unsigned HorizontalDelta = HorizontalEnd - HorizontalStart;

float convertHorizontalValue(unsigned value) {
    unsigned temp = value * 10000 / HorizontalDelta;
    temp *= 2;
    int32_t stemp = temp - 10000;
    return 1.0f * stemp / 10000;
}

UiObjectPtr Converter::getUiObject(std::shared_ptr<const GameObject> gameObject) const {
    UiObjectPtr uiObject(new UiObject);
    uiObject->setXValue(0, convertHorizontalValue(gameObject->horizontalPosition));
    uiObject->setYValue(0, (( (float) WINDOW_SIZE_V - gameObject->verticalPosition) / WINDOW_SIZE_V) * 2.0f - 1.0f);
    uiObject->setZValue(0, 0);

    uiObject->setXValue(1, convertHorizontalValue(gameObject->horizontalPosition + gameObject->horizontalSize));
    uiObject->setYValue(1, (( (float) WINDOW_SIZE_V - gameObject->verticalPosition) / WINDOW_SIZE_V) * 2.0f - 1.0f);
    uiObject->setZValue(1, 0);

    uiObject->setXValue(2, convertHorizontalValue(gameObject->horizontalPosition + gameObject->horizontalSize));
    uiObject->setYValue(2, (( (float) WINDOW_SIZE_V - gameObject->verticalPosition - gameObject->verticalSize) / WINDOW_SIZE_V) * 2.0f - 1.0f);
    uiObject->setZValue(2, 0);

    uiObject->setXValue(3, convertHorizontalValue(gameObject->horizontalPosition));
    uiObject->setYValue(3, (( (float) WINDOW_SIZE_V - gameObject->verticalPosition - gameObject->verticalSize) / WINDOW_SIZE_V) * 2.0f - 1.0f);
    uiObject->setZValue(3, 0);

    return uiObject;
}

UiObjectPtrVector Converter::getUiObjects(const std::vector<std::shared_ptr<GameObject>>& gameObjects) const {
    UiObjectPtrVector uiObjects;
    uiObjects.reserve(gameObjects.size());

    for (std::shared_ptr<GameObject> gameObject : gameObjects) {
        UiObjectPtr geometricObject = getUiObject(gameObject);
        uiObjects.push_back(geometricObject);
    }

    return uiObjects;
}