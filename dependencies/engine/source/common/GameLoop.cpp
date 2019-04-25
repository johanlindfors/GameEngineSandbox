#include "GameLoop.h"
#include "SimpleRenderer.h"
#include "IOC.hpp"
#include "scenes/GameScene.h"
#include "textures/TextureManager.h"
#include "input/InputManager.h"
#include "sprites/SpriteRenderer.h"
#include "StepTimer.h"

using namespace std;
using namespace Engine;
using namespace Utilities;

GameLoop::GameLoop() 
	: mSimpleRenderer(nullptr)
	, mIsInitialized(false)
{

}

void GameLoop::Initialize() {
	//mSimpleRenderer = new SimpleRenderer();


	IOCContainer::Instance().Register<ITextureManager>(make_shared<TextureManager>());

	mSpriteRenderer = make_shared<SpriteRenderer>();
	IOCContainer::Instance().Register<ISpriteRenderer>(mSpriteRenderer);
	
	mInputManager = make_shared<InputManager>();
	IOCContainer::Instance().Register<IInputManager>(mInputManager);	

	mTimer = make_shared<StepTimer>();
	mTimer->SetFixedTimeStep(true);
	mTimer->SetTargetElapsedSeconds(1.0f/15.0f);

	// Game must register callback
	mGameLoopCallback = IOCContainer::Instance().Resolve<IGameLoopCallback>();
	mGameLoopCallback->Initialize();

	mIsInitialized = true;
}

GameLoop::~GameLoop() {
	if (mSimpleRenderer) {
		delete (mSimpleRenderer);
	}
}

void GameLoop::Tick() {
	if (!mIsInitialized)
		return;
	mTimer->Tick([&]() { Update(); });
	Render();
}

void GameLoop::UpdateWindowSize(int width, int height) {
	// TODO: Handle window size changed events
	if (!mIsInitialized)
		return;
	//mSimpleRenderer->UpdateWindowSize(width, height);
	mGameLoopCallback->UpdateScreenSize(width, height);
	mSpriteRenderer->UpdateWindowSize(width, height);
}

void GameLoop::GetDefaultSize(int &width, int &height) const {
	// TODO: Change to desired default window size (note minimum size is 320x200).
	width = 800;
	height = 600;
}

void GameLoop::Update() {
	if (!mIsInitialized)
		return;

	// TODO: Add your game logic here.
	mGameLoopCallback->Update(mTimer);	
}

void GameLoop::Render() {
	if (!mIsInitialized)
		return;

	// Don't try to render anything before the first Update.
	if (mTimer->GetFrameCount() == 0) {
		return;
	}

	Clear();

	mGameLoopCallback->Draw(mTimer);
	//mSimpleRenderer->Draw(mTimer);
}

void GameLoop::Clear() {
	// TODO: Add your clearing code here
	mSpriteRenderer->Clear();
}
