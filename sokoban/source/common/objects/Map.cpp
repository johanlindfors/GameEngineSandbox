#include "Map.hpp"
#include "renderers/SpriteRenderer.hpp"
#include "utilities/IOC.hpp"
#include "resources/IResourceManager.hpp"
#include "objects/Crate.hpp"
#include "game/GameDefines.hpp"
#include "objects/FixedTile.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;

Map::Map()
{
    printf("[Map::constructor]\n");
    int index = 0;
    for(int value : PARSED_MAP){
        mLevel[index++] = value;
    }
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
