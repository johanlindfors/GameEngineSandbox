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
	: mSprite(make_shared<Sprite>())
	, mMillisecondsToLoad(2000.0f)
	, hasLoadedGamePlay(false)
	, isLoadingResources(false)
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
	fileNames.emplace_back(L"bird.png");
	mTextureManager->LoadTextures(vector<wstring>(fileNames));

	// Textures
	//mResourcesToLoad.push(L"bird.png");
	// mResourcesToLoad.push(L"cityscape.png");
	// mResourcesToLoad.push(L"clouds.png");
	// mResourcesToLoad.push(L"gameover.png");
	// mResourcesToLoad.push(L"get-ready.png");
	// mResourcesToLoad.push(L"ground.png");
	// mResourcesToLoad.push(L"instructions.png");
	// mResourcesToLoad.push(L"medals.png");
	// mResourcesToLoad.push(L"pipes.png");
	// mResourcesToLoad.push(L"scoreboard.png");
	// //mResourcesToLoad.push(L"sky.png");
	// mResourcesToLoad.push(L"start-button.png");
	// mResourcesToLoad.push(L"title.png");
	// mResourcesToLoad.push(L"trees.png");

	// Audio
	// mResourcesToLoad.push(L"background.png");

	mSprite->Texture = mTextureManager->GetTexture(L"bird.png");
    printf("[SplashScene::Load] Loaded\n");
}

void SplashScene::Unload() { }

void SplashScene::UpdateScreenSize(int width, int height) 
{
	const auto spriteAspectRatio = static_cast<float>(mSprite->Texture.Height) / static_cast<float>(mSprite->Texture.Width);
	const auto screenAspectRatio = static_cast<float>(height) / static_cast<float>(width);
	if (screenAspectRatio > spriteAspectRatio) {
		mSprite->Height = static_cast<int>(width * spriteAspectRatio);
		mSprite->Width = width;
	}
	else {
		mSprite->Height = height;
		mSprite->Width = static_cast<int>(height / spriteAspectRatio);
	}
	cout << "mSprite w: " << width << " h: " << height << std::endl;
					
	mSprite->Position = { 0, 0};// { width / 2.0f - mSprite->Width / 2.0f, height / 2.0f - mSprite->Height / 2.0f };
}

void SplashScene::Update(shared_ptr<IStepTimer> timer)
{
	isLoadingResources = true;
	if(mResourcesToLoad.size() > 0) {
	    printf("[SplashScene::Update] Loading resource\n");
		vector<wstring> fileNames;
		fileNames.emplace_back(mResourcesToLoad.front());
		mResourcesToLoad.pop();
		mTextureManager->LoadTextures(vector<wstring>(fileNames));
		printf("[SplashScene::Update] Resource loaded\n");
	}
	isLoadingResources = false;
	// mMillisecondsToLoad -= static_cast<float>((timer->GetElapsedSeconds() * 1000.0f));
	// if (mMillisecondsToLoad <= 0 && mResourcesToLoad.size() == 0) {
	// 	auto sceneManager = IOCContainer::Instance().Resolve<ISceneManager>();
	// 	if (!hasLoadedGamePlay) {
	// 		mGame->GoToState(GameState::GamePlay);
	// 		hasLoadedGamePlay = true;
	// 	}
	// }
}

void SplashScene::Draw(shared_ptr<IStepTimer> /*timer*/)
{
	if (mSpriteRenderer && !isLoadingResources) {
		mSpriteRenderer->DrawSprite(mSprite);
	}
}
