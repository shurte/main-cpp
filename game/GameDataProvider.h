#pragma once

#include <GameObject.h>

#include <memory>
#include <vector>

class GameDataProvider {
    public:
        std::vector<std::shared_ptr<GameObject>> getGameObjects();
};