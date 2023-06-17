#pragma once
#include <vector>
#include "objects/Crate.hpp"
#include "utilities/MathHelper.hpp"
#include <functional>
#include <vector>

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
        void initialize(std::vector<int> level);
        void draw(std::shared_ptr<Engine::IRenderer> renderer);
        bool isWalkable(int x, int y);
        bool isCrate(int x, int y);
        void moveCrate(int deltaX, int deltaY, int playerX, int playerY, std::function<void()> onCompleteCallback);
        bool checkWin();

        Utilities::Point<int> playerStartPosition;
        static std::shared_ptr<Map> parse(std::string input);

    private:
        int mLevel[100];
        std::vector<std::shared_ptr<FixedTile>> mFixedTiles;
        std::vector<std::shared_ptr<Crate>> mCrates;
};