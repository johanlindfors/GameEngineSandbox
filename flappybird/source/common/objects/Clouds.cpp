#include "Clouds.h"
#include "utilities/IStepTimer.h"
#include "renderer/ISpriteRenderer.h"
#include "renderer/Sprite.h"

using namespace std;
using namespace Engine;
using namespace Utilities;

Clouds::Clouds(Vector2 position, Vector2 velocity)
    : mPosition(position)
    , mVelocity(velocity)
    , mClouds(make_shared<Sprite>())
    , mCloudsBackground(make_shared<Sprite>())
{
    mClouds->Position = Vector2(position.m[0], position.m[1] + 200);
    mClouds->Width = 351;
    mClouds->Height = 33;
    mClouds->Offset = 5;

    mCloudsBackground->Position = Vector2(position.m[0], position.m[1]);
    mCloudsBackground->Width = 288;
    mCloudsBackground->Height = 200;
    mCloudsBackground->Offset = 18;   
}

void Clouds::Update(shared_ptr<IStepTimer> timer)
{
    mPosition.m[0] += mVelocity.m[0] * (timer->GetElapsedMilliSeconds()/1000.0f);
    if(mPosition.m[0] <= -351.0) {
        mPosition.m[0] += 351.0;
    }
}

void Clouds::Draw(shared_ptr<ISpriteRenderer> renderer)
{
    renderer->DrawSprite(mClouds, mPosition);
    renderer->DrawSprite(mClouds, Vector2(mPosition.m[0] + 351, mPosition.m[1]));
    renderer->DrawSprite(mCloudsBackground, Vector2(0, mPosition.m[1]-200));
}
