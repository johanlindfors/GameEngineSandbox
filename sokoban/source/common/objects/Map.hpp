#pragma once
#include <vector>
#include "objects/Crate.hpp"
#include "utilities/MathHelper.hpp"

namespace Engine
{
    class IRenderer;
}

namespace Utilities
{
    class IStepTimer;
}

class FixedTile;

class Map {
    public:
        Map();
        ~Map();
        void initialize();
        void update(std::shared_ptr<Utilities::IStepTimer> timer);
        void draw(std::shared_ptr<Engine::IRenderer> renderer);
        Utilities::Point<int> playerStartPosition;

    private:
        int mLevel[100];
        std::vector<std::shared_ptr<FixedTile>> mFixedTiles;
        std::vector<std::shared_ptr<Crate>> mCrates;
};