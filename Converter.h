#pragma once

#include <GameObject.h>
#include <UiObject.h>

#include <memory>
#include <vector>

class Converter {
    public:
        UiObjectPtr getUiObject(std::shared_ptr<GameObject> gameObject) const;
        UiObjectPtrVector getUiObjects(const std::vector<std::shared_ptr<GameObject>>& gameObjects) const;
};