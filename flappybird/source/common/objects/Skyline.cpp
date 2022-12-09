#include "Skyline.h"
#include "utilities/IStepTimer.h"
#include "renderer/ISpriteRenderer.h"
#include "renderer/Sprite.h"

using namespace std;
using namespace Engine;
using namespace Utilities;

Skyline::Skyline(Point<float> position, Vector2 velocity)
    : mSprite(make_shared<Sprite>())
    , mVelocity(velocity)
    , mSkyline(vector<Point<float>>())
{
    mSprite->Width = 86;
    mSprite->Height = 42,
    mSprite->Offset = 4;

    for (size_t i = 0; i < 6; i++)
    {
        auto point = Point<float>(position.X + i * 86, position.Y);
        mSkyline.push_back(point);
    }
}

void Skyline::Update(shared_ptr<IStepTimer> timer)
{
    for(auto & position: mSkyline) {
        position.X += (mVelocity.m[0] * timer->GetElapsedMilliSeconds() / 1000.0f);
        if(position.X < -100.0) {
            position.X += 6 * 86;
        } 
    }
}

void Skyline::Draw(shared_ptr<ISpriteRenderer> renderer)
{
    for(auto const& position: mSkyline) {
        renderer->DrawSprite(mSprite, Point<float>(position.X, position.Y));
    }
}
