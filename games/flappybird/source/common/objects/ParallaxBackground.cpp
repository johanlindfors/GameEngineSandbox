#include "ParallaxBackground.hpp"
#include "renderers/SpriteRenderer.hpp"
#include "objects/Clouds.hpp"
#include "objects/Trees.hpp"
#include "objects/Skyline.hpp"
#include "objects/Ground.hpp"
#include "sprites/Sprite.hpp"
#include "game/GameDefines.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;

ParallaxBackground::ParallaxBackground()
    : mClouds(make_unique<Clouds>(Point<float>{0, 172}, Vector2{SCROLL_SPEED * 0.25f, 0})),
      mSkyline(make_unique<Skyline>(Point<float>{0, 133}, Vector2{SCROLL_SPEED * 0.5f, 0})),
      mTrees(make_unique<Trees>(Point<float>{0, 113}, Vector2{SCROLL_SPEED * 0.75f, 0})),
      mIsRunning(true)
{
}

ParallaxBackground::~ParallaxBackground()
{
    mClouds.reset();
    mSkyline.reset();
    mTrees.reset();
}

void ParallaxBackground::initializeSprites()
{
    mClouds->initializeSprite();
    mSkyline->initializeSprite();
    mTrees->initializeSprite();
}

void ParallaxBackground::update(shared_ptr<IStepTimer> timer)
{
    if (mIsRunning)
    {
        mClouds->update(timer);
        mSkyline->update(timer);
        mTrees->update(timer);
    }
}

void ParallaxBackground::draw(shared_ptr<IRenderer> renderer)
{
    mClouds->draw(renderer);
    mSkyline->draw(renderer);
    mTrees->draw(renderer);
}
