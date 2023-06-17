#include "Map.hpp"
#include "renderers/SpriteRenderer.hpp"
#include "utilities/IOC.hpp"
#include "resources/IResourceManager.hpp"
#include "objects/Crate.hpp"
#include "game/GameDefines.hpp"
#include "objects/FixedTile.hpp"
#include <algorithm>
#include <functional>

using namespace std;
using namespace Engine;
using namespace Utilities;

Map::Map(vector<int> level)
{
    printf("[Map::constructor]\n");
    int index = 0;
    for(int value : level){
        mLevel[index++] = value;
    }
    printf("[Map::constructor] %d\n", index);
}

Map::~Map()
{
    printf("[Map::destructor]\n");
}

void Map::initialize()
{
    printf("[Map::initialize]\n");
    for(int index = 0; index < 100; index++) {
        int x = index % 10;
        int y = index / 10;
        switch(mLevel[index]) {
            case PLAYER:
            case PLAYER+SPOT:
                playerStartPosition = { x, y };
                mFixedTiles.emplace_back(make_shared<FixedTile>(x, y, mLevel[index] - PLAYER));
                mLevel[index] -= PLAYER;
                break;

            case CRATE:
            case CRATE+SPOT:
                mCrates.emplace_back(make_shared<Crate>(x, y));
                mFixedTiles.emplace_back(make_shared<FixedTile>(x, y, mLevel[index] - CRATE));
                break;

            default:
                mFixedTiles.emplace_back(make_shared<FixedTile>(x, y, mLevel[index]));
                break;
        }
    }
}

void Map::update(shared_ptr<IStepTimer> timer)
{
    for(const auto crate : mCrates) {
        crate->update(timer);
    }
}

void Map::draw(shared_ptr<IRenderer> renderer)
{
	auto spriteRenderer = static_pointer_cast<SpriteRenderer>(renderer);
	if(spriteRenderer) {
        for(const auto tile : mFixedTiles) {
            tile->draw(renderer);
        }
        for(const auto crate : mCrates) {
            crate->draw(renderer);
        }
	}
}

bool Map::isWalkable(int x, int y) {
    int index = y * 10 + x;
    return mLevel[index] == EMPTY || mLevel[index] == SPOT;
}

bool Map::isCrate(int x, int y){
    int index = y * 10 + x;
    return mLevel[index] == CRATE || mLevel[index] == CRATE+SPOT;
}

void Map::moveCrate(int deltaX, int deltaY, int playerX, int playerY, function<void()> onCompleteCallback) {
    int oldCrateIndex = (playerY + deltaY) * 10 + playerX + deltaX;
    int newCrateIndex = (playerY + 2 * deltaY) * 10 + playerX + 2 * deltaX;

    mLevel[oldCrateIndex] -= CRATE;
    mLevel[newCrateIndex] += CRATE;

    auto it = std::find_if(mCrates.begin(), mCrates.end(), [oldCrateIndex](shared_ptr<Crate> crate) { return crate->index == oldCrateIndex; });
    auto crate = it->get();
    crate->index = newCrateIndex;
    crate->move(deltaX, deltaY, onCompleteCallback);
}

bool Map::checkWin()
{
    for(auto value : mLevel) {
        if(value == SPOT) {
            return false;
        }
    }
    return true;
}
