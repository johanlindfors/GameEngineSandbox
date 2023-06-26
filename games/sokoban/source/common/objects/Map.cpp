#include "Map.hpp"

//stl
#include <algorithm>
#include <functional>
#include <sstream>
#include <vector>

// engine
#include "renderers/SpriteRenderer.hpp"
#include "utilities/IOC.hpp"
#include "resources/IResourceManager.hpp"

// game
#include "objects/Crate.hpp"
#include "game/GameDefines.hpp"
#include "objects/FixedTile.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;

void Map::initialize(std::vector<int> level)
{
    printf("[Map::initialize] Begin\n");
    copy(level.begin(), level.end(), mLevel.begin());
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
    printf("[Map::initialize] End\n");
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
    auto frame = mLevel[crate->index];
    crate->move(deltaX, deltaY, [crate, frame, onCompleteCallback](){
        crate->setFrame(frame);
        onCompleteCallback();
    });
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

shared_ptr<Map> Map::parse(string input) {
    printf("[Map::parse] parsing input\n");
    std::istringstream parsed(input);
    vector<int> level;
    char c;
    while(parsed.get(c)) {
        switch (c)
        {
            case '|':
            case '\r':
            case '\n':
                break;
        case '#':
            level.emplace_back(1);
            break;
        case '$':
            level.emplace_back(3);
            break;
        case '@':
            level.emplace_back(4);
            break;
        case '.':
            level.emplace_back(2);
            break;
        default:
            level.emplace_back(0);
            break;
        }
    }
    printf("[Map::parse] parsed fetch input\n");
    struct MkShrdEnablr : public Map {};
    auto map = make_shared<MkShrdEnablr>();
    map->initialize(level);
    printf("[Map::parse] initialized level\n");
    return map;
}
