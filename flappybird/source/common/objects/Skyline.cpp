#include "Skyline.h"
#include "utilities/IStepTimer.h"
#include "renderer/ISpriteRenderer.h"
#include "renderer/Sprite.h"

using namespace std;
using namespace Engine;
using namespace Utilities;

Skyline::Skyline(Point position, Vector2 velocity)
    : mPosition(position)
    , mVelocity(velocity)
    , mSkyline(vector<shared_ptr<Sprite>>())
{
    for (size_t i = 0; i < 6; i++)
    {
        auto skyline = make_shared<Sprite>();
        skyline->Position.X = mPosition.X + i * 86;
        skyline->Position.Y = mPosition.Y;
        skyline->Width = 86;
        skyline->Height = 42;
        skyline->Offset = 4;
        mSkyline.push_back(skyline);
    }
}

void Skyline::Update(shared_ptr<IStepTimer> timer)
{
    for(auto skyline: mSkyline) {
        skyline->Position.X += mVelocity.m[0] * (timer->GetElapsedMilliSeconds()/1000.0f);
        if(skyline->Position.X <= -100) {
            skyline->Position.X += 6 * 86;
        } 
    }
}

void Skyline::Draw(shared_ptr<ISpriteRenderer> renderer)
{
    for(auto skyline: mSkyline) {
        renderer->DrawSprite(skyline, skyline->Position);
    }
}
