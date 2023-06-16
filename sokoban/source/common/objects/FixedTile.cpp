#include "FixedTile.hpp"
#include "renderers/SpriteRenderer.hpp"
#include "renderers/Sprite.hpp"
#include "game/GameDefines.hpp"
#include "utilities/IOC.hpp"
#include "resources/IResourceManager.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;

FixedTile::FixedTile(int x, int y, int frame)
{
    auto resourceManager = IOCContainer::instance().resolve<IResourceManager>();
    mSprite = make_shared<Engine::Sprite>();
    mSprite->texture = resourceManager->getTexture( "tiles.png" );
    mSprite->size = { TILE_SIZE, TILE_SIZE };
    mSprite->position = { static_cast<float>(x * TILE_SIZE), static_cast<float>(y * TILE_SIZE) };
    mSprite->offset = { TILE_SIZE / 280.0f * frame, 0.0f, TILE_SIZE / 280.0f, 1.0f };
}

FixedTile::~FixedTile()
{

}

void FixedTile::draw(shared_ptr<IRenderer> renderer)
{
    auto spriteRenderer = static_pointer_cast<SpriteRenderer>(renderer);
    if(spriteRenderer) {
        spriteRenderer->drawSprite(mSprite);
    }
}