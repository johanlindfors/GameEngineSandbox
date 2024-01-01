#pragma once

// stl
#include <vector>
#include <array>
#include <string>
#include <functional>

// engine
#include "utilities/MathHelper.hpp"

namespace Engine
{
    class IRenderer;
}

namespace Engine
{
    class IStepTimer;
}

class FixedTile;
class Crate;

class Map
{
public:
    void initialize(std::vector<int> level);
    void draw(std::shared_ptr<Engine::IRenderer> renderer);
    bool isWalkable(int x, int y);
    bool isCrate(int x, int y);
    void moveCrate(int deltaX, int deltaY, int playerX, int playerY, std::function<void()> onCompleteCallback);
    bool checkWin();

    Engine::Point<int> playerStartPosition;
    static std::shared_ptr<Map> parse(std::string input);

private:
    std::array<int, 100> mLevel = {};
    std::vector<std::shared_ptr<FixedTile>> mFixedTiles;
    std::vector<std::shared_ptr<Crate>> mCrates;
};
