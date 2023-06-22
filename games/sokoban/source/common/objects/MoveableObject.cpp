#include "MoveableObject.hpp"
#include "utilities/IOC.hpp"
#include "renderers/SpriteRenderer.hpp"
#include "sprites/Sprite.hpp"
#include "resources/IResourceManager.hpp"
#include "game/GameDefines.hpp"
#include "utilities/TweenEngine.hpp"
#include "utilities/IStepTimer.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;

MoveableObject::MoveableObject()
    : isMoving(false)
{
    printf("[MoveableObject::constructor]\n");
}

void MoveableObject::draw(shared_ptr<IRenderer> renderer)
{
    auto spriteRenderer = static_pointer_cast<SpriteRenderer>(renderer);
	if(spriteRenderer) {
        spriteRenderer->drawSprite(mSprite);
    }
}

void MoveableObject::move(int deltaX, int deltaY, function<void()> onCompleteCallback)
{
    auto tweenEngine(IOCContainer::instance().resolve<ITweenEngine>());

    if(deltaX != 0) {
        tweenEngine->add(
            mSprite->position.x,
            mSprite->position.x + (deltaX * TILE_SIZE),
            [&](float value)
            {
                mSprite->position.x = value;
            },  
            150 * 1000, 
            false,
            onCompleteCallback);
    }
    if(deltaY != 0) {
        tweenEngine->add(
            mSprite->position.y,
            mSprite->position.y + (deltaY * TILE_SIZE),
            [&](float value)
            {
                mSprite->position.y = value;
            },  
            150 * 1000, 
            false,
            onCompleteCallback);    
    }
}
