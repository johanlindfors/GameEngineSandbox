#include "Skyline.h"
#include "utilities/IStepTimer.h"
#include "renderers/ISpriteRenderer.h"
#include "renderers/Sprite.h"

using namespace std;
using namespace Engine;
using namespace Utilities;

Skyline::Skyline(Point<float> position, Vector2 velocity)
    : mSprite(make_shared<Sprite>())
    , mVelocity(velocity)
    , mSkyline(vector<Point<float>>())
{
    mSprite->width = 86;
    mSprite->height = 42,
    mSprite->offset = 4;

    for (size_t i = 0; i < 6; i++)
    {
        auto point = Point<float>{position.x + i * 86, position.y};
        mSkyline.push_back(point);
    }
}

void Skyline::update(shared_ptr<IStepTimer> timer)
{
    for(auto & position: mSkyline) {
        position.x += (mVelocity.x * timer->getElapsedMilliSeconds());
        if(position.x < -100.0) {
            position.x += 6 * 86;
        } 
    }
}

void Skyline::draw(shared_ptr<ISpriteRenderer> renderer)
{
    for(auto const& position: mSkyline) {
        renderer->drawSprite(mSprite, position);
    }
}
