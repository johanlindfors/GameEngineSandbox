#include "GameLoop.h"
#include "SimpleRenderer.h"
#include "IOC.hpp"
#include "scenes/GameScene.h"
#include "textures/TextureManager.h"

using namespace std;
using namespace Engine;

GameLoop::GameLoop() : mIsInitialized(false) {}

void GameLoop::Initialize() {
	mSimpleRenderer = new SimpleRenderer();

	mSceneManager = make_shared<SceneManager>();
	IOCContainer::Instance().Register<SceneManager>(mSceneManager);
	IOCContainer::Instance().Register<ITextureManager>(make_shared<TextureManager>());

	auto initialSceneFromGame = IOCContainer::Instance().Resolve<GameScene>();
	mSceneManager->AddScene(initialSceneFromGame);

	mTimer.SetFixedTimeStep(true);
	mIsInitialized = true;
}

GameLoop::~GameLoop() {
	delete (mSimpleRenderer);
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
	mSimpleRenderer->UpdateWindowSize(width, height);
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
	mSimpleRenderer->Update(mTimer);
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

	mSimpleRenderer->Draw(mTimer);
	mSceneManager->Draw(mTimer);
}

void GameLoop::Clear() {
	// TODO: Add your clearing code here
}
