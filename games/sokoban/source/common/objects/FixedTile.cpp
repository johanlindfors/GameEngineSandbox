#include "FixedTile.hpp"

// engine
#include "renderers/SpriteRenderer.hpp"
#include "sprites/TiledSprite.hpp"
#include "utilities/IOC.hpp"
#include "resources/IResourceManager.hpp"

// game
#include "game/GameDefines.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;

FixedTile::FixedTile(int x, int y, int frame)
{
    auto resourceManager = IOCContainer::instance().resolve<IResourceManager>();
    mSprite = make_shared<Engine::TiledSprite>();
    mSprite->currentTile = frame;
    mSprite->tileSize = { 128, 128 };
    mSprite->texture = resourceManager->getTexture( TILES );
    mSprite->size = { TILE_SIZE, TILE_SIZE };
    mSprite->position = { static_cast<float>(x * TILE_SIZE), static_cast<float>(y * TILE_SIZE) };
    mSprite->calculateTileOffset();
}

void FixedTile::draw(shared_ptr<IRenderer> renderer)
{
    auto spriteRenderer = static_pointer_cast<SpriteRenderer>(renderer);
    if(spriteRenderer) {
        spriteRenderer->drawSprite(mSprite);
    }
}
