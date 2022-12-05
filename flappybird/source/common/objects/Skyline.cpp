#include "Skyline.h"
#include "utilities/IStepTimer.h"
#include "renderer/ISpriteRenderer.h"
#include "renderer/Sprite.h"

using namespace std;
using namespace Engine;
using namespace Utilities;

Skyline::Skyline(Vector2 position, Vector2 velocity)
    : mPosition(position)
    , mVelocity(velocity)
    , mSkyline(vector<shared_ptr<Sprite>>())
{
    for (size_t i = 0; i < 6; i++)
    {
        auto skyline = make_shared<Sprite>();
        skyline->Position.m[0] = mPosition.m[0] + i * 86;
        skyline->Position.m[1] = mPosition.m[1];
        skyline->Width = 86;
        skyline->Height = 42;
        skyline->Offset = 4;
        mSkyline.push_back(skyline);
    }
}

void Skyline::Update(shared_ptr<IStepTimer> timer)
{
    for(auto skyline: mSkyline) {
        skyline->Position.m[0] += mVelocity.m[0] * (timer->GetElapsedMilliSeconds()/1000.0f);
        if(skyline->Position.m[0] <= -100) {
            skyline->Position.m[0] += 6 * 86;
        } 
    }
}

void Skyline::Draw(shared_ptr<ISpriteRenderer> renderer)
{
    for(auto skyline: mSkyline) {
        renderer->DrawSprite(skyline, skyline->Position);
    }
}
