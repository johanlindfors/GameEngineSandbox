#include "Crate.hpp"
#include "utilities/IStepTimer.hpp"
#include "sprites/TiledSprite.hpp"
#include "renderers/SpriteRenderer.hpp"
#include "game/GameDefines.hpp"
#include "utilities/IOC.hpp"
#include "resources/IResourceManager.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;

Crate::Crate(int x, int y)
    : index(y * 10 +x)
{
    auto sprite = make_shared<TiledSprite>();
    sprite->texture = IOCContainer::instance().resolve<IResourceManager>()->getTexture( TILES );
    sprite->size = { TILE_SIZE, TILE_SIZE };
    sprite->tileSize = { 128, 128 };

    sprite->position = {
        static_cast<float>(x) * TILE_SIZE, 
        static_cast<float>(y) * TILE_SIZE
    };
    sprite->setFrame(3);
    mSprite = sprite;
}

void Crate::setFrame(int frame) 
{
    auto sprite = static_pointer_cast<TiledSprite>(mSprite);
    sprite->setFrame(frame);
}
