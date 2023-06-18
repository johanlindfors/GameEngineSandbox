#include "FixedTile.hpp"
#include "renderers/SpriteRenderer.hpp"
#include "renderers/TiledSprite.hpp"
#include "game/GameDefines.hpp"
#include "utilities/IOC.hpp"
#include "resources/IResourceManager.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;

FixedTile::FixedTile(int x, int y, int frame)
{
    auto resourceManager = IOCContainer::instance().resolve<IResourceManager>();
    mTiledSprite = make_shared<Engine::TiledSprite>();
    mTiledSprite->currentTile = frame;
    mTiledSprite->tileSize = { 128, 128 };
    mTiledSprite->texture = resourceManager->getTexture( TILES );
    mTiledSprite->size = { TILE_SIZE, TILE_SIZE };
    mTiledSprite->position = { static_cast<float>(x * TILE_SIZE), static_cast<float>(y * TILE_SIZE) };
    mTiledSprite->calculateTileOffset();
}

void FixedTile::draw(shared_ptr<IRenderer> renderer)
{
    auto spriteRenderer = static_pointer_cast<SpriteRenderer>(renderer);
    if(spriteRenderer) {
        spriteRenderer->drawSprite(mTiledSprite);
    }
}
