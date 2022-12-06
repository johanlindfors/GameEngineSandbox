#include "Clouds.h"
#include "utilities/IStepTimer.h"
#include "renderer/ISpriteRenderer.h"
#include "renderer/Sprite.h"

using namespace std;
using namespace Engine;
using namespace Utilities;

Clouds::Clouds(Point position, Vector2 velocity)
    : mPosition(position)
    , mVelocity(velocity)
    , mClouds(make_shared<Sprite>())
    , mCloudsBackground(make_shared<Sprite>())
{
    mClouds->Position = Point(position.X, position.Y + 200);
    mClouds->Width = 351;
    mClouds->Height = 33;
    mClouds->Offset = 5;

    mCloudsBackground->Position = Point(position.X, position.Y);
    mCloudsBackground->Width = 288;
    mCloudsBackground->Height = 200;
    mCloudsBackground->Offset = 18;   
}

void Clouds::Update(shared_ptr<IStepTimer> timer)
{
    mPosition.X += mVelocity.m[0] * (timer->GetElapsedMilliSeconds() / 1000.0f);
    if(mPosition.X <= -351.0) {
        mPosition.X += 351.0;
    }
}

void Clouds::Draw(shared_ptr<ISpriteRenderer> renderer)
{
    renderer->DrawSprite(mClouds, mPosition);
    renderer->DrawSprite(mClouds, Point(mPosition.X + 351, mPosition.Y));
    renderer->DrawSprite(mCloudsBackground, Point(0, mPosition.Y - 200));
}
