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
        auto ground = Point<float>{position.X + i * 23, position.Y};
        mGround.push_back(ground);
    }

    mGroundSprite->Width = 23;
    mGroundSprite->Height = 26;
    mGroundSprite->Offset = 15;

    mGroundBackgroundSprite->Position = Point<float>{position.X, position.Y-200};
    mGroundBackgroundSprite->Width = 288;
    mGroundBackgroundSprite->Height = 200;
    mGroundBackgroundSprite->Offset = 20;

    AABB.Width = 288;
    AABB.Height = 105;
    AABB.Position.Y = 0;
    
#if defined(_DEBUG) && (DEBUG_TEXTURES_ENABLED == true)
    mGroundDebugSprite->Width = 288;
    mGroundDebugSprite->Height = 105;
    mGroundDebugSprite->Offset = 22;
#endif
}

void Ground::Update(shared_ptr<IStepTimer> timer)
{
    if(!mIsRunning)
        return;
    for(auto &ground: mGround) {
        ground.X += (mVelocity.idx[0] * timer->GetElapsedMilliSeconds() / 1000.0);
        if(ground.X <= -30) {
            ground.X += 14 * 23;
        } 
    }
}

void Ground::Draw(shared_ptr<ISpriteRenderer> renderer)
{
    renderer->DrawSprite(mGroundBackgroundSprite, mGroundBackgroundSprite->Position);
    for(auto position: mGround) {
        renderer->DrawSprite(mGroundSprite, position);
    }
#if defined(_DEBUG) && (DEBUG_TEXTURES_ENABLED == true)
    renderer->DrawSprite(mGroundDebugSprite);
#endif
}
