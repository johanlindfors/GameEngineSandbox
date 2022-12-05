#include "Ground.h"
#include "utilities/IStepTimer.h"
#include "renderer/ISpriteRenderer.h"
#include "renderer/Sprite.h"

using namespace std;
using namespace Engine;
using namespace Utilities;

Ground::Ground(Vector2 position, Vector2 velocity)
    : mPosition(position)
    , mVelocity(velocity)
    , mGround(vector<shared_ptr<Sprite>>())
    , mGroundBackground(make_shared<Sprite>())
    , ICollidable::ICollidable(Vector2(0,0))
#ifdef _DEBUG
    , mGroundDebugSprite(make_shared<Sprite>())
#endif
{
    for (size_t i = 0; i < 14; i++)
    {
        auto ground = make_shared<Sprite>();
        ground->Position = Vector2(position.m[0] + i * 23, position.m[1] + 200);
        ground->Width = 23;
        ground->Height = 26;
        ground->Offset = 15;
        mGround.push_back(ground);
    }

    mGroundBackground->Position = Vector2(position.m[0], position.m[1]);
    mGroundBackground->Width = 288;
    mGroundBackground->Height = 200;
    mGroundBackground->Offset = 20;

    AABB.Width = 288;
    AABB.Height = 155;

#ifdef _DEBUG
    mGroundDebugSprite->Width = 288;
    mGroundDebugSprite->Height = 155;
    mGroundDebugSprite->Offset = 22;
#endif
}

void Ground::Update(shared_ptr<IStepTimer> timer)
{
    for(auto ground: mGround) {
        ground->Position.m[0] += mVelocity.m[0] * (timer->GetElapsedMilliSeconds()/1000.0f);
        if(ground->Position.m[0] <= -30) {
            ground->Position.m[0] += 14 * 23;
        } 
    }
}

void Ground::Draw(shared_ptr<ISpriteRenderer> renderer)
{
    renderer->DrawSprite(mGroundBackground, mGroundBackground->Position);
    for(auto ground: mGround) {
        renderer->DrawSprite(ground, ground->Position);
    }
#ifdef _DEBUG
    renderer->DrawSprite(mGroundDebugSprite);
#endif
}
