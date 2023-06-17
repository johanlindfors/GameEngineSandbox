#include "MoveableObject.hpp"
#include "utilities/IOC.hpp"
#include "renderers/SpriteRenderer.hpp"
#include "renderers/Sprite.hpp"
#include "resources/IResourceManager.hpp"
#include "game/GameDefines.hpp"
#include "utilities/TweenEngine.hpp"
#include "utilities/IStepTimer.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;

MoveableObject::MoveableObject()
    : isMoving(false)
    , mTweenEngine(IOCContainer::instance().resolve<ITweenEngine>())
{
    printf("[MoveableObject::constructor]\n");
    auto resourceManager = IOCContainer::instance().resolve<IResourceManager>();
    mSprite = make_shared<Engine::Sprite>();
    mSprite->texture = resourceManager->getTexture( TILES );
    mSprite->size = { TILE_SIZE, TILE_SIZE };
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
    if(deltaX != 0) {
        mTweenEngine->add(
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
        mTweenEngine->add(
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

void MoveableObject::setFrame(int frame) 
{
    mSprite->offset = { TILE_SIZE / 280.0f * frame, 0.0f, TILE_SIZE / 280.0f, 1.0f };
}