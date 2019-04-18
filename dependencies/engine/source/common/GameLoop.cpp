#include "GameLoop.h"
#include "SimpleRenderer.h"
#include "IOC.hpp"
#include "scenes/GameScene.h"
#include "textures/TextureManager.h"
#include "input/InputManager.h"
#include "sprites/SpriteRenderer.h"

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

	// Initialize
	mSceneManager = make_shared<SceneManager>();
	IOCContainer::Instance().Register<ISceneManager>(mSceneManager);
	mSceneManager->Initialize();

	IOCContainer::Instance().Register<ITextureManager>(make_shared<TextureManager>());

	mSpriteRenderer = make_shared<SpriteRenderer>();
	IOCContainer::Instance().Register<ISpriteRenderer>(mSpriteRenderer);
	
	// Game must register initial scen
	auto initialSceneFromGame = IOCContainer::Instance().Resolve<GameScene>();
	IOCContainer::Instance().Remove<GameScene>();
	mSceneManager->AddScene(initialSceneFromGame);

	mInputManager = make_shared<InputManager>();
	IOCContainer::Instance().Register<IInputManager>(mInputManager);	

	mTimer.SetFixedTimeStep(true);
	mIsInitialized = true;
}

GameLoop::~GameLoop() {
	if (mSimpleRenderer) {
		delete (mSimpleRenderer);
	}
	mSceneManager.reset();
}

void GameLoop::Tick() {
	if (!mIsInitialized)
		return;
	mTimer.Tick([&]() { Update(); });
	Render();
}

void GameLoop::UpdateWindowSize(int width, int height) {
	// TODO: Handle window size changed events
	if (!mIsInitialized)
		return;
	//mSimpleRenderer->UpdateWindowSize(width, height);
	mSceneManager->UpdateScreenSize(width, height);
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

	float elapsedTime = float(mTimer.GetElapsedSeconds());

	// TODO: Add your game logic here.
	elapsedTime;
	mSceneManager->Update(mTimer);
}

void GameLoop::Render() {
	if (!mIsInitialized)
		return;

	// Don't try to render anything before the first Update.
	if (mTimer.GetFrameCount() == 0) {
		return;
	}

	Clear();

	//mSimpleRenderer->Draw(mTimer);
	mSceneManager->Draw(mTimer);
}

void GameLoop::Clear() {
	// TODO: Add your clearing code here
	mSpriteRenderer->Clear();
}
