#include "ParallaxBackground.h"
#include "renderer/ISpriteRenderer.h"
#include "objects/Clouds.h"
#include "objects/Trees.h"
#include "objects/Skyline.h"
#include "objects/Ground.h"
#include "renderer/Sprite.h"

using namespace std;
using namespace Engine;
using namespace Utilities;

ParallaxBackground::ParallaxBackground()
	: mBackground(make_shared<Sprite>())
	, mClouds(make_unique<Clouds>(Vector2(0,210), Vector2(-10,0)))
	, mTrees(make_unique<Trees>(Vector2(0,175), Vector2(-15,0)))
	, mSkyline(make_unique<Skyline>(Vector2(0,155), Vector2(-20,0)))
	, mGround(make_unique<Ground>(Vector2(0,-70), Vector2(-30,0)))
{
	mBackground->Offset = 3;
	mBackground->Width = 288;
	mBackground->Height = 505;
}

ParallaxBackground::~ParallaxBackground() 
{

}

void ParallaxBackground::Update(shared_ptr<IStepTimer> timer)
{
	mClouds->Update(timer);
	mTrees->Update(timer);
	mSkyline->Update(timer);
	mGround->Update(timer);
}

void ParallaxBackground::Draw(shared_ptr<ISpriteRenderer> renderer)
{
    renderer->DrawSprite(mBackground);
    mClouds->Draw(renderer);
    mTrees->Draw(renderer);
    mSkyline->Draw(renderer);
    mGround->Draw(renderer);
}
