#include "SplashScene.h"
#include "IOC.hpp"
#include "scenes/ISceneManager.h"
#include "game/IGameStateCallback.h"
#include "textures/ITextureManager.h"
#include "renderer/ISpriteRenderer.h"
#include "renderer/Sprite.h"
#include "IStepTimer.h"
#include <iostream>
#include "objects/ParallaxBackground.h"
#include "objects/Bird.h"

using namespace std;
using namespace Engine;
using namespace Utilities;

SplashScene::SplashScene(IGameStateCallback* gameCallback)
	: mBackground(make_shared<ParallaxBackground>())
	, mTitle(make_shared<Sprite>())
	, mBird(make_unique<Bird>(Vector2(132,250)))
	, mMillisecondsToLoad(2000.0f)
	, mHasLoadedGamePlay(false)
	, mIsLoadingResources(true)
	, mWindowWidth(0)
	, mWindowHeight(0)
	, mGame(gameCallback)
{
	ID = typeid(SplashScene).name();
}

SplashScene::~SplashScene() { }

void SplashScene::Load()
{
	mTextureManager = IOCContainer::Instance().Resolve<ITextureManager>();
    mSpriteRenderer = IOCContainer::Instance().Resolve<ISpriteRenderer>();
    
	vector<wstring> fileNames;
	fileNames.emplace_back(L"atlas.png");
	mTextureManager->LoadTextures(vector<wstring>(fileNames));

	// Audio
	// mResourcesToLoad.push(L"background.png");

	mTitle->Offset = 13;
	mTitle->Width = 179;
	mTitle->Height = 48;

    printf("[SplashScene::Load] Loaded\n");
}

void SplashScene::Unload() { }

void SplashScene::UpdateScreenSize(int width, int height) 
{
	if(mWindowWidth == width && mWindowHeight == height)
		return;

	mTitle->Position = Vector2(
		width/2 - mTitle->Width/2, 
		height/2 - mTitle->Height/2 + 100
	);

	mWindowWidth = width;
	mWindowHeight = height;
}

void SplashScene::Update(shared_ptr<IStepTimer> timer)
{
	auto milliseconds = static_cast<float>(timer->GetElapsedMilliSeconds());
	mMillisecondsToLoad -= milliseconds;
	mBackground->Update(timer);

	mBird->Update(timer);
	if (mMillisecondsToLoad <= 0) {
		if (!mHasLoadedGamePlay) {
			mGame->GoToState(GameState::GamePlay);
			mHasLoadedGamePlay = true;
		}
	}
}

void SplashScene::Draw(shared_ptr<IStepTimer> /*timer*/)
{
	if (mSpriteRenderer) {
		mBackground->Draw(mSpriteRenderer);
		mSpriteRenderer->DrawSprite(mTitle);
		mBird->Draw(mSpriteRenderer);
	}
}
