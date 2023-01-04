#include "Trees.h"
#include "utilities/IStepTimer.h"
#include "renderers/ISpriteRenderer.h"
#include "renderers/Sprite.h"

using namespace std;
using namespace Engine;
using namespace Utilities;

Trees::Trees(Point<float> position, Vector2 velocity)
    : mPosition(position)
    , mVelocity(velocity)
    , mTrees(make_shared<Sprite>())
    , mTreesBackground(make_shared<Sprite>())
{
    mTrees->width = 415;
    mTrees->height = 32;
    mTrees->offset = 14;

    mTreesBackground->width = 415;
    mTreesBackground->height = 200;
    mTreesBackground->offset = 19;   
}

void Trees::update(shared_ptr<IStepTimer> timer)
{
    mPosition.x += (mVelocity.x * timer->getElapsedMilliSeconds());
    if(mPosition.x <= -415.0) {
        mPosition.x += 415.0;
    }
}

void Trees::draw(shared_ptr<ISpriteRenderer> renderer)
{
    renderer->drawSprite(mTrees, mPosition);
    renderer->drawSprite(mTrees, Point<float>{mPosition.x + 415, mPosition.y});
    renderer->drawSprite(mTreesBackground, Point<float>{0, mPosition.y - 200});
}
