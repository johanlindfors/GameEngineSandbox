#include "ParallaxBackground.h"
#include "renderer/ISpriteRenderer.h"
#include "objects/Clouds.h"
#include "objects/Trees.h"
#include "objects/Skyline.h"
#include "objects/Ground.h"
#include "renderer/Sprite.h"
#include "game/GameDefines.h"

using namespace std;
using namespace Engine;
using namespace Utilities;

ParallaxBackground::ParallaxBackground()
	: mClouds(make_unique<Clouds>(Vector2(0,210), Vector2(CLOUD_SPEED,0)))
	, mSkyline(make_unique<Skyline>(Vector2(0,175), Vector2(SKYLINE_SPEED,0)))
	, mTrees(make_unique<Trees>(Vector2(0,150), Vector2(TREES_SPEED,0)))
	, mGround(make_shared<Ground>(Vector2(0,-70), Vector2(GROUND_SPEED,0)))
    , mIsRunning(true)
{
}

ParallaxBackground::~ParallaxBackground() 
{
    mClouds.release();
    mSkyline.release();
    mTrees.release();
    mGround.reset();
}

void ParallaxBackground::Update(shared_ptr<IStepTimer> timer)
{
    if(mIsRunning) {
        mClouds->Update(timer);
        mSkyline->Update(timer);
        mTrees->Update(timer);
        mGround->Update(timer);
    }
}

void ParallaxBackground::Draw(shared_ptr<ISpriteRenderer> renderer)
{
    mClouds->Draw(renderer);
    mSkyline->Draw(renderer);
    mTrees->Draw(renderer);
    mGround->Draw(renderer);
}
