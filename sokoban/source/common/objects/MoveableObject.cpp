#include "MoveableObject.hpp"
#include "utilities/IOC.hpp"
#include "renderers/SpriteRenderer.hpp"
#include "renderers/Sprite.hpp"
#include "resources/IResourceManager.hpp"
#include "game/GameDefines.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;

MoveableObject::MoveableObject()
    : mFrame(0)
{
    auto resourceManager = IOCContainer::instance().resolve<IResourceManager>();
    mSprite = make_shared<Engine::Sprite>();
    mSprite->texture = resourceManager->getTexture( "tiles.png" );
    mSprite->size = { TILE_SIZE, TILE_SIZE };
}

MoveableObject::~MoveableObject()
{

}

void MoveableObject::update()
{
    mSprite->offset = { TILE_SIZE / 280.0f * mFrame, 0.0f, TILE_SIZE / 280.0f, 1.0f };
}

void MoveableObject::draw(shared_ptr<IRenderer> renderer)
{
    auto spriteRenderer = static_pointer_cast<SpriteRenderer>(renderer);
	if(spriteRenderer) {
        spriteRenderer->drawSprite(mSprite);
    }
}