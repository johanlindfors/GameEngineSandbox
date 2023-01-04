#include "ParallaxBackground.h"
#include "renderers/ISpriteRenderer.h"
#include "objects/Clouds.h"
#include "objects/Trees.h"
#include "objects/Skyline.h"
#include "objects/Ground.h"
#include "renderers/Sprite.h"
#include "game/GameDefines.h"

using namespace std;
using namespace Engine;
using namespace Utilities;

ParallaxBackground::ParallaxBackground()
	: mClouds(make_unique<Clouds>(Point<float>{0, 172}, Vector2{SCROLL_SPEED * 0.25f, 0}))
	, mSkyline(make_unique<Skyline>(Point<float>{0, 133}, Vector2{SCROLL_SPEED * 0.5f, 0}))
	, mTrees(make_unique<Trees>(Point<float>{0, 113}, Vector2{SCROLL_SPEED * 0.75f, 0}))
    , mIsRunning(true)
{
}

ParallaxBackground::~ParallaxBackground() 
{
    mClouds.reset();
    mSkyline.reset();
    mTrees.reset();
}

void ParallaxBackground::update(shared_ptr<IStepTimer> timer)
{
    if(mIsRunning) {
        mClouds->update(timer);
        mSkyline->update(timer);
        mTrees->update(timer);
    }
}

void ParallaxBackground::draw(shared_ptr<ISpriteRenderer> renderer)
{
    mClouds->draw(renderer);
    mSkyline->draw(renderer);
    mTrees->draw(renderer);
}
