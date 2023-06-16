#include "MoveableObject.hpp"
#include "utilities/IOC.hpp"
#include "renderers/SpriteRenderer.hpp"
#include "renderers/Sprite.hpp"
#include "resources/IResourceManager.hpp"
#include "game/GameDefines.hpp"
#include "utilities/TweenEngine.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;

MoveableObject::MoveableObject()
    : mFrame(0)
    , isMoving(false)
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

void MoveableObject::move(int deltaX, int deltaY)
{
    isMoving = true;
    auto tweenEngine = IOCContainer::instance().resolve<ITweenEngine>();
    if(deltaX != 0) {
        tweenEngine->add(static_cast<int>(mSprite->position.x), [&](int value)
        {
            mSprite->position.x = static_cast<float>(value);
        }, mSprite->position.x + (deltaX * TILE_SIZE), 150, false,
        [&]() { isMoving = false; });
    }
    if(deltaY != 0) {
        tweenEngine->add(static_cast<int>(mSprite->position.y), [&](int value)
        {
            mSprite->position.y = static_cast<float>(value);
        }, mSprite->position.y + (deltaY * TILE_SIZE), 150, false,
        [&]() { isMoving = false; });
    }
}