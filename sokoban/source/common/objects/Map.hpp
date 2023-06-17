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
        bool isWalkable(int x, int y);
        bool isCrate(int x, int y);
        void moveCrate(int deltaX, int deltaY, int playerX, int playerY);

        Utilities::Point<int> playerStartPosition;

    private:
        bool checkWin();
        int mLevel[100];
        std::vector<std::shared_ptr<FixedTile>> mFixedTiles;
        std::vector<std::shared_ptr<Crate>> mCrates;
};