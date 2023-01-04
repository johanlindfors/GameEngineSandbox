#include "Trees.h"
#include "utilities/IStepTimer.h"
#include "renderers/ISpriteRenderer.h"
#include "renderers/Sprite.h"

using namespace std;
using namespace Engine;
using namespace Utilities;

Trees::Trees(Point<float> position, Vector2 velocity)
    : mPosition(Point<float>{position.X, position.Y})
    , mVelocity(velocity)
    , mTrees(make_shared<Sprite>())
    , mTreesBackground(make_shared<Sprite>())
{
    mTrees->Width = 415;
    mTrees->Height = 32;
    mTrees->Offset = 14;

    mTreesBackground->Width = 415;
    mTreesBackground->Height = 200;
    mTreesBackground->Offset = 19;   
}

void Trees::Update(shared_ptr<IStepTimer> timer)
{
    mPosition.X += (mVelocity.idx[0] * timer->GetElapsedMilliSeconds());
    if(mPosition.X <= -415.0) {
        mPosition.X += 415.0;
    }
}

void Trees::Draw(shared_ptr<ISpriteRenderer> renderer)
{
    renderer->DrawSprite(mTrees, Point<float>{mPosition.X, mPosition.Y});
    renderer->DrawSprite(mTrees, Point<float>{mPosition.X + 415, mPosition.Y});
    renderer->DrawSprite(mTreesBackground, Point<float>{0, mPosition.Y-200});
}
