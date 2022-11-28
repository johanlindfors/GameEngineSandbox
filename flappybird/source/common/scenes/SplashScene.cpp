#include "SplashScene.h"
#include "IOC.hpp"
#include "scenes/ISceneManager.h"
#include "game/IGameStateCallback.h"
#include "textures/ITextureManager.h"
#include "renderer/ISpriteRenderer.h"
#include "renderer/Sprite.h"
#include "IStepTimer.h"
#include <iostream>

using namespace std;
using namespace Engine;
using namespace Utilities;

SplashScene::SplashScene(IGameStateCallback* gameCallback)
	: mBackground(make_shared<Sprite>())
	, mTitle(make_shared<Sprite>())
	, mClouds(make_unique<Clouds>(Vector2(0,200), Vector2(-10,0)))
	// , mGround(make_shared<Sprite>())
	// , mTrees(make_shared<Sprite>())
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

	//mBackground->Texture = mTextureManager->GetTexture(L"atlas.png");
	mBackground->Offset = 3;
	mBackground->Width = 288;
	mBackground->Height = 505;

	//mTitle->Texture = mTextureManager->GetTexture(L"atlas.png");
	mTitle->Offset = 13;
	mTitle->Width = 179;
	mTitle->Height = 48;

	// mClouds->Offset = 5;
	// mClouds->Width = 288;
	// mClouds->Height = 200;

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
	mClouds->Update(timer);
	// mTitle->Position.m[1] -= milliseconds/10;
	// if (mMillisecondsToLoad <= 0 && mResourcesToLoad.size() == 0) {
	// 	if (!mHasLoadedGamePlay) {
	// 		mGame->GoToState(GameState::GamePlay);
	// 		mHasLoadedGamePlay = true;
	// 	}
	// }
}

void SplashScene::Draw(shared_ptr<IStepTimer> /*timer*/)
{
	if (mSpriteRenderer) {
		mSpriteRenderer->DrawSprite(mBackground);
		mClouds->Draw(mSpriteRenderer);
		// mSpriteRenderer->DrawSprite(mTrees);
		// mSpriteRenderer->DrawSprite(mCity);
		// mSpriteRenderer->DrawSprite(mGround);
		mSpriteRenderer->DrawSprite(mTitle);
	}
}
