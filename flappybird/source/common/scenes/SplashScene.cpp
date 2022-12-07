#include "SplashScene.h"
#include "utilities/IOC.hpp"
#include "scenes/ISceneManager.h"
#include "game/IGameStateCallback.h"
#include "textures/ITextureManager.h"
#include "input/IInputManager.h"
#include "renderer/ISpriteRenderer.h"
#include "renderer/Sprite.h"
#include "utilities/IStepTimer.h"
#include <iostream>
#include "objects/ParallaxBackground.h"
#include "objects/Bird.h"

using namespace std;
using namespace Engine;
using namespace Utilities;

SplashScene::SplashScene(IGameStateCallback* gameCallback)
	: mBackground(make_shared<Sprite>())
	, mSkyline(make_shared<ParallaxBackground>())
	, mTitle(make_shared<Sprite>())
	, mInstructions(make_shared<Sprite>())
	, mMillisecondsToLoad(2000.0f)
	, mHasLoadedGamePlay(false)
	, mIsLoadingResources(true)
	, mWindowWidth(0)
	, mWindowHeight(0)
	, mGame(gameCallback)
{
	ID = typeid(SplashScene).name();
	mBackground->Offset = 3;
	mBackground->Width = 288;
	mBackground->Height = 505;
	
	mInstructions->Offset = 6;
	mInstructions->Position = Point<float>(96,180);
	mInstructions->Width = 103;
	mInstructions->Height = 102;

	mSkyline->Pause();
}

SplashScene::~SplashScene() {
	mBackground.reset();
 }

void SplashScene::Load()
{
	mTextureManager = IOCContainer::Instance().Resolve<ITextureManager>();
	mInputManager = IOCContainer::Instance().Resolve<IInputManager>();
    
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

	mTitle->Position = Point<float>(
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
	mSkyline->Update(timer);
	
	auto const spacePressed = mInputManager->IsKeyDown(32);
	if (mGame->GetCurrentState() == GameState::GamePlay) {
		if (spacePressed && !mSpacePressedBefore) {
			if (!mHasLoadedGamePlay) {
				mGame->GoToState(GameState::GamePlay);
				mHasLoadedGamePlay = true;
			}
		}
	}
	else {
		if (spacePressed && !mSpacePressedBefore) {
			mGame->GoToState(GameState::GamePlay);
		}
	}
	mSpacePressedBefore = spacePressed;
}

void SplashScene::Draw(shared_ptr<ISpriteRenderer> renderer)
{
	if (renderer) {
		renderer->DrawSprite(mBackground);
		mSkyline->Draw(renderer);
		renderer->DrawSprite(mTitle);
		renderer->DrawSprite(mInstructions);
	}
}
