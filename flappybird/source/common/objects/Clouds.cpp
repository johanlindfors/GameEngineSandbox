#include "Clouds.h"
#include "utilities/IStepTimer.h"
#include "renderers/ISpriteRenderer.h"
#include "renderers/Sprite.h"

using namespace std;
using namespace Engine;
using namespace Utilities;

Clouds::Clouds(Point<float> position, Vector2 velocity)
    : mPosition(position)
    , mVelocity(velocity)
    , mClouds(make_shared<Sprite>())
    , mCloudsBackground(make_shared<Sprite>())
{
    mClouds->position = Point<float>{position.x, position.y + 200};
    mClouds->width = 351;
    mClouds->height = 33;
    mClouds->offset = 5;

    mCloudsBackground->position = Point<float>{position.x, position.y};
    mCloudsBackground->width = 288;
    mCloudsBackground->height = 200;
    mCloudsBackground->offset = 18;   
}

void Clouds::update(shared_ptr<IStepTimer> timer)
{
    mPosition.x += (mVelocity.x * timer->getElapsedMilliSeconds());
    if(mPosition.x <= -351.0) {
        mPosition.x += 351.0;
    }
}

void Clouds::draw(shared_ptr<ISpriteRenderer> renderer)
{
    renderer->drawSprite(mClouds, mPosition);
    renderer->drawSprite(mClouds, Point<float>{mPosition.x + 351, mPosition.y});
    renderer->drawSprite(mCloudsBackground, Point<float>{0, mPosition.y - 200});
}
