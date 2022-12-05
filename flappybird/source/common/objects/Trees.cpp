#include "Trees.h"
#include "utilities/IStepTimer.h"
#include "renderer/ISpriteRenderer.h"
#include "renderer/Sprite.h"

using namespace std;
using namespace Engine;
using namespace Utilities;

Trees::Trees(Vector2 position, Vector2 velocity)
    : mPosition(position)
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
    mPosition.m[0] += mVelocity.m[0] * (timer->GetElapsedMilliSeconds()/1000.0f);
    if(mPosition.m[0] <= -415.0) {
        mPosition.m[0] += 415.0;
    }
}

void Trees::Draw(shared_ptr<ISpriteRenderer> renderer)
{
    renderer->DrawSprite(mTrees, mPosition);
    renderer->DrawSprite(mTrees, Vector2(mPosition.m[0] + 415, mPosition.m[1]));
    renderer->DrawSprite(mTreesBackground, Vector2(0, mPosition.m[1]-200));
}
