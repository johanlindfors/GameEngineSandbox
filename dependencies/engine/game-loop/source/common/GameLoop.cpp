#include "game-loop/GameLoop.h"
#include "IOC.hpp"
#include "scenes/SceneManager.h"
#include "input/InputManager.h"
#include "textures/TextureManager.h"
#include "renderer/SpriteRenderer.h"
#include "StepTimer.h"
#include "game-loop/IGameLoopCallback.h"
#include "filesystem/FileSystem.h"

using namespace std;
using namespace Engine;
using namespace Utilities;

GameLoop::GameLoop() 
	: mIsInitialized(false) { }

void GameLoop::Initialize(int fps) {
	mTimer = make_shared<StepTimer>();
	mTimer->SetFixedTimeStep(true);
	mTimer->SetTargetElapsedSeconds(1.0f/fps);

	// Ordering is important
	const auto fileSystem = make_shared<FileSystem>();
	IOCContainer::Instance().Register<IFileSystem>(fileSystem);

	const auto textureManager = make_shared<TextureManager>();
	IOCContainer::Instance().Register<ITextureManager>(textureManager);

	mSpriteRenderer = make_shared<SpriteRenderer>();
	// IOCContainer::Instance().Register<ISpriteRenderer>(mSpriteRenderer);

	// mInputManager = make_shared<InputManager>();
	// IOCContainer::Instance().Register<IInputManager>(mInputManager);

	// mSceneManager = make_shared<SceneManager>();
	// IOCContainer::Instance().Register<ISceneManager>(mSceneManager);

	// mSceneManager->Initialize();

	// // Game must register callback
	// mGameLoopCallback = IOCContainer::Instance().Resolve<IGameLoopCallback>();
	// mGameLoopCallback->Initialize();

	mIsInitialized = true;
}

GameLoop::~GameLoop() { }

void GameLoop::Tick() {
	if (!mIsInitialized)
		return;
	mTimer->Tick([&]() { Update(); });
	Render();
}

void GameLoop::UpdateWindowSize(int width, int height)
{
	// TODO: Handle window size changed events
	if (!mIsInitialized)
		return;
	mSpriteRenderer->UpdateWindowSize(width, height);
	mSceneManager->UpdateScreenSize(width, height);
}

void GameLoop::GetDefaultSize(int &width, int &height)
{
	// TODO: Change to desired default window size (note minimum size is 320x200).
	width = 500;
	height = 500;
}

void GameLoop::Update() const
{
	if (!mIsInitialized)
		return;

	// TODO: Add your game logic here.
	mGameLoopCallback->Update(mTimer);	
	mSceneManager->Update(mTimer);
}

void GameLoop::Render() {
	if (!mIsInitialized)
		return;

	// Don't try to render anything before the first Update.
	if (mTimer->GetFrameCount() == 0) {
		return;
	}

	Clear();

	mSceneManager->Draw(mTimer);
}

void GameLoop::Clear() const
{
	// TODO: Add your clearing code here
	mSpriteRenderer->Clear();
}
