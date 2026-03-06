#pragma once

#include <GameObject.h>
#include <UiObject.h>

#include <memory>
#include <vector>

class Converter {
    public:
        std::shared_ptr<UiObject> getUiObject(const GameObject& gameObject) const;
        std::vector<std::shared_ptr<UiObject>> getUiObjects(const std::vector<GameObject>& gameObjects) const;
};