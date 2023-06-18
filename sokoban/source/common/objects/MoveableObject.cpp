#include "MoveableObject.hpp"
#include "utilities/IOC.hpp"
#include "renderers/SpriteRenderer.hpp"
#include "renderers/TiledSprite.hpp"
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
    mTiledSprite = make_shared<Engine::AnimatedSprite>();
    mTiledSprite->texture = resourceManager->getTexture( TILES );
    mTiledSprite->size = { TILE_SIZE, TILE_SIZE };
    mTiledSprite->tileSize = { 128, 128 };
}

void MoveableObject::draw(shared_ptr<IRenderer> renderer)
{
    auto spriteRenderer = static_pointer_cast<SpriteRenderer>(renderer);
	if(spriteRenderer) {
        spriteRenderer->drawSprite(mTiledSprite);
    }
}

void MoveableObject::move(int deltaX, int deltaY, function<void()> onCompleteCallback)
{
    if(deltaX != 0) {
        mTweenEngine->add(
            mTiledSprite->position.x,
            mTiledSprite->position.x + (deltaX * TILE_SIZE),
            [&](float value)
            {
                mTiledSprite->position.x = value;
            },  
            150 * 1000, 
            false,
            onCompleteCallback);
    }
    if(deltaY != 0) {
        mTweenEngine->add(
            mTiledSprite->position.y,
            mTiledSprite->position.y + (deltaY * TILE_SIZE),
            [&](float value)
            {
                mTiledSprite->position.y = value;
            },  
            150 * 1000, 
            false,
            onCompleteCallback);    
    }
}

void MoveableObject::setFrame(int frame) 
{
    mTiledSprite->currentTile = frame;
    mTiledSprite->calculateTileOffset();
}
