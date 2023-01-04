#include "SplashScene.h"
#include "utilities/IOC.hpp"
#include "scenes/ISceneManager.h"
#include "game/IGameStateCallback.h"
#include "resources/IResourceManager.h"
#include "input/IInputManager.h"
#include "renderers/ISpriteRenderer.h"
#include "renderers/Sprite.h"
#include "utilities/IStepTimer.h"
#include "utilities/ILazyInitialized.h"
#include <iostream>
#include "objects/ParallaxBackground.h"
#include "objects/Bird.h"
#include "objects/Ground.h"

using namespace std;
using namespace Engine;
using namespace Utilities;

SplashScene::SplashScene(IGameStateCallback* gameCallback)
	: mBackground(make_shared<Sprite>())
	, mSkyline(make_shared<ParallaxBackground>())
	, mGround(make_shared<Ground>(Point<float>{0,79}, Vector2{SCROLL_SPEED,0}))
	, mTitle(make_shared<Sprite>())
	, mButton(make_shared<Sprite>())
	, mBird(make_shared<Bird>(Point<float>{0,0}))
	, mMillisecondsToLoad(2000.0f)
	, mHasLoadedGamePlay(false)
	, mIsLoadingResources(true)
	, mWindowWidth(0)
	, mWindowHeight(0)
	, mGame(gameCallback)
{
	id = typeid(SplashScene).name();
	mBackground->offset = 3;
	mBackground->width = 288;
	mBackground->height = 505;
	
	mButton->offset = 12;
	mButton->width = 104;
	mButton->height = 58;
	mButton->position = Point<float>{92,176};
}

SplashScene::~SplashScene() {
	mBackground.reset();
 }

void SplashScene::load()
{
	mResourceManager = IOCContainer::instance().resolve<IResourceManager>();
	mInputManager = IOCContainer::instance().resolve<IInputManager>();
    
	vector<string> fileNames;
	fileNames.emplace_back("atlas.png");
	mResourceManager->loadTextures(vector<string>(fileNames));
	mResourceManager->loadShader("spritesheet", "vertex.glsl", "fragment.glsl");
	mResourceManager->loadShader("fontsheet", "vertex.glsl", "fragment.glsl");
	auto lazyInitializedTypes = IOCContainer::instance().resolve<LazyInitializedTypes>();
	for (auto it = lazyInitializedTypes->begin(); it != lazyInitializedTypes->end(); ++it) {
		it->get()->lazyInitialize();
	}
	
	// Audio
	// mResourcesToLoad.push(L"background.png");

	mTitle->offset = 13;
	mTitle->width = 179;
	mTitle->height = 48;

    printf("[SplashScene::load] Loaded\n");
}

void SplashScene::unload() { }

void SplashScene::updateScreenSize(int width, int height) 
{
	if(mWindowWidth == width && mWindowHeight == height)
		return;

	mTitle->position = Point<float>{30.0f, height - 100.0f - mTitle->height};
	mBird->position = Point<float>{230.0f, height - 129.0f};

	mWindowWidth = width;
	mWindowHeight = height;
}

void SplashScene::update(shared_ptr<IStepTimer> timer)
{
	auto milliseconds = static_cast<float>(timer->getElapsedMilliSeconds());
	mMillisecondsToLoad -= milliseconds;
	mSkyline->update(timer);
	mGround->update(timer);
	
	auto const spacePressed = mInputManager->isKeyDown(32);
	if (spacePressed && !mSpacePressedBefore) {
		mGame->goToState(GameState::Instructions);
	}
	mSpacePressedBefore = spacePressed;
}

void SplashScene::draw(shared_ptr<IRenderer> renderer)
{
	auto spriteRenderer = static_pointer_cast<ISpriteRenderer>(renderer);
	if (spriteRenderer) {
		spriteRenderer->drawSprite(mBackground);
		mSkyline->draw(spriteRenderer);
		spriteRenderer->drawSprite(mTitle);
		spriteRenderer->drawSprite(mButton);
		mGround->draw(spriteRenderer);
		mBird->draw(spriteRenderer);
	}
}
