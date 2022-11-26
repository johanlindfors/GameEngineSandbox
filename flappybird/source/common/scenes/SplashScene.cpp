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

	mBackground->Texture = mTextureManager->GetTexture(L"atlas.png");
    printf("[SplashScene::Load] Loaded\n");
}

void SplashScene::Unload() { }

void SplashScene::UpdateScreenSize(int width, int height) 
{
	if(mWindowWidth == width && mWindowHeight == height)
		return;

	mWindowWidth = width;
	mWindowHeight = height;

	mBackground->Width = mBackground->Texture.Width;
	mBackground->Height = mBackground->Texture.Height;

	mTitle->Width = mTitle->Texture.Width;
	mTitle->Height = mTitle->Texture.Height;

	float positionX = width / 2.0f - mTitle->Texture.Width / 2.0f;
	float positionY = height / 2.0f - mTitle->Texture.Height / 2.0f;

	mBackground->Position = { 0, 0 };
	mTitle->Position = { positionX, positionY + 500 };
}

void SplashScene::Update(shared_ptr<IStepTimer> timer)
{
	if(mResourcesToLoad.size() > 0) {
		vector<wstring> fileNames;
		fileNames.emplace_back(mResourcesToLoad.front());
		mResourcesToLoad.pop();
		mTextureManager->LoadTextures(vector<wstring>(fileNames));
	} else {
		mIsLoadingResources = false;
		auto milliseconds = static_cast<float>(timer->GetElapsedMilliSeconds());
		mMillisecondsToLoad -= milliseconds;
		mTitle->Position.m[1] -= milliseconds/10;
		// if (mMillisecondsToLoad <= 0 && mResourcesToLoad.size() == 0) {
		// 	if (!mHasLoadedGamePlay) {
		// 		mGame->GoToState(GameState::GamePlay);
		// 		mHasLoadedGamePlay = true;
		// 	}
		// }
	}
}

void SplashScene::Draw(shared_ptr<IStepTimer> /*timer*/)
{
	if (mSpriteRenderer) {
		//printf("[SplashScene::Draw] Render sprite\n");
		mSpriteRenderer->DrawSprite(mBackground);
		mSpriteRenderer->DrawSprite(mTitle);
	}
}
