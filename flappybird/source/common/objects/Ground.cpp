#include "Ground.h"
#include "utilities/IStepTimer.h"
#include "renderers/ISpriteRenderer.h"
#include "renderers/Sprite.h"

using namespace std;
using namespace Engine;
using namespace Utilities;

Ground::Ground(Point<float> position, Vector2 velocity)
    : mPosition(position)
    , mVelocity(velocity)
    , mGround(vector<Point<float>>())
    , mGroundSprite(make_shared<Sprite>())
    , mGroundBackgroundSprite(make_shared<Sprite>())
    , ICollidable::ICollidable(position)
    , mIsRunning(true)

#if defined(_DEBUG) && (DEBUG_TEXTURES_ENABLED == true)
    , mGroundDebugSprite(make_shared<Sprite>())
#endif
{
    for (size_t i = 0; i < 14; i++)
    {
        auto ground = Point<float>{position.x + i * 23, position.y};
        mGround.push_back(ground);
    }

    mGroundSprite->width = 23;
    mGroundSprite->height = 26;
    mGroundSprite->offset = 15;

    mGroundBackgroundSprite->position = Point<float>{position.x, position.y - 200};
    mGroundBackgroundSprite->width = 288;
    mGroundBackgroundSprite->height = 200;
    mGroundBackgroundSprite->offset = 20;

    AABB.width = 288;
    AABB.height = 105;
    AABB.position.y = 0;
    
#if defined(_DEBUG) && (DEBUG_TEXTURES_ENABLED == true)
    mGroundDebugSprite->width = 288;
    mGroundDebugSprite->height = 105;
    mGroundDebugSprite->offset = 22;
#endif
}

void Ground::update(shared_ptr<IStepTimer> timer)
{
    if(!mIsRunning)
        return;
    for(auto &ground: mGround) {
        ground.x += (mVelocity.x * timer->getElapsedMilliSeconds());
        if(ground.x <= -30) {
            ground.x += 14 * 23;
        } 
    }
}

void Ground::draw(shared_ptr<ISpriteRenderer> renderer)
{
    renderer->drawSprite(mGroundBackgroundSprite, mGroundBackgroundSprite->position);
    for(auto position: mGround) {
        renderer->drawSprite(mGroundSprite, position);
    }
#if defined(_DEBUG) && (DEBUG_TEXTURES_ENABLED == true)
    renderer->drawSprite(mGroundDebugSprite);
#endif
}
