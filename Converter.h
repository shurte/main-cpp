#pragma once

#include <GameObject.h>
#include <UiObject.h>

#include <memory>
#include <vector>

class Converter {
    public:
        UiObjectPtr getUiObject(const GameObject& gameObject) const;
        UiObjectPtrVector getUiObjects(const std::vector<GameObject>& gameObjects) const;
};