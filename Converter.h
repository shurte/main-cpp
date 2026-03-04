#pragma once

#include <GameObject.h>
#include <UiObject.h>

#include <vector>

class Converter {
    public:
        UiObject getUiObject(const GameObject& gameObject) const;
        std::vector<UiObject> getUiObjects(const std::vector<GameObject>& gameObjects) const;
};