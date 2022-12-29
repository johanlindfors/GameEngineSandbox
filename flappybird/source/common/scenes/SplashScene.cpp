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
	, mGround(make_shared<Ground>(Point<float>(0,79), Vector2(SCROLL_SPEED,0)))
	, mTitle(make_shared<Sprite>())
	, mButton(make_shared<Sprite>())
	, mBird(make_shared<Bird>(Point<float>(0,0)))
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
	
	mButton->Offset = 12;
	mButton->Width = 104;
	mButton->Height = 58;
	mButton->Position = Point<float>(92,176);
}

SplashScene::~SplashScene() {
	mBackground.reset();
 }

void SplashScene::Load()
{
	mResourceManager = IOCContainer::Instance().Resolve<IResourceManager>();
	mInputManager = IOCContainer::Instance().Resolve<IInputManager>();
    
	vector<string> fileNames;
	fileNames.emplace_back("atlas.png");
	mResourceManager->LoadTextures(vector<string>(fileNames));
	mResourceManager->LoadShader("spritesheet", "vertex.glsl", "fragment.glsl");
	mResourceManager->LoadShader("fontsheet", "vertex.glsl", "fragment.glsl");
	auto lazyInitializedTypes = IOCContainer::Instance().Resolve<LazyInitializedTypes>();
	for (auto it = lazyInitializedTypes->begin(); it != lazyInitializedTypes->end(); ++it) {
		it->get()->LazyInitialize();
	}
	
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

	mTitle->Position = Point<float>(30.0f, height - 100.0f - mTitle->Height);
	mBird->Position = Point<float>(230.0f, height - 129.0f);

	mWindowWidth = width;
	mWindowHeight = height;
}

void SplashScene::Update(shared_ptr<IStepTimer> timer)
{
	auto milliseconds = static_cast<float>(timer->GetElapsedMilliSeconds());
	mMillisecondsToLoad -= milliseconds;
	mSkyline->Update(timer);
	mGround->Update(timer);
	
	// auto const spacePressed = mInputManager->IsKeyDown(32);
	// if (spacePressed && !mSpacePressedBefore) {
	// 	mGame->GoToState(GameState::Instructions);
	// }
	// mSpacePressedBefore = spacePressed;

	auto const mouseState = mInputManager->GetMouseState();
	if(mouseState.State == MouseButtonState::Pressed) {
		auto position = mouseState.Position;
		if(position.X > 92 && 
		   position.X < 92 + 104 &&
		   position.Y > 176 &&
		   position.Y < 176 + 58)
		{
			mGame->GoToState(GameState::Instructions);
	    }
	}
}

void SplashScene::Draw(shared_ptr<ISpriteRenderer> renderer)
{
	if (renderer) {
		renderer->DrawSprite(mBackground);
		mSkyline->Draw(renderer);
		renderer->DrawSprite(mTitle);
		renderer->DrawSprite(mButton);
		mGround->Draw(renderer);
		mBird->Draw(renderer);
	}
}
