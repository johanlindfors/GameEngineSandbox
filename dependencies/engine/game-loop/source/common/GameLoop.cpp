#include "game-loop/GameLoop.h"
#include "utilities/IOC.hpp"
#include "utilities/Config.h"
#include "scenes/SceneManager.h"
#include "input/InputManager.h"
#include "resources/ResourceManager.h"
#include "renderers/ISpriteRenderer.h"
#include "StepTimer.h"
#include "game-loop/IGameLoopCallback.h"
#include "filesystem/FileSystem.h"

using namespace std;
using namespace Engine;
using namespace Utilities;

GameLoop::GameLoop() 
	: mIsInitialized(false) { }

void GameLoop::Initialize(shared_ptr<Config> config) {
	mTimer = make_shared<StepTimer>();
	mTimer->SetFixedTimeStep(config->UseFixedTimeStep);
	mTimer->SetTargetElapsedSeconds(1.0f/config->FPS);

    printf("[GameLoop::Initialize] Timer initialized\n");

	// Ordering is important
	const auto fileSystem = make_shared<FileSystem>();
	IOCContainer::Instance().Register<IFileSystem>(fileSystem);
	printf("[GameLoop::Initialize] FileSystem registered\n");

	const auto resourceManager = make_shared<ResourceManager>();
	IOCContainer::Instance().Register<IResourceManager>(resourceManager);
    printf("[GameLoop::Initialize] ResourceeManager registered\n");

	mSpriteRenderer = IOCContainer::Instance().Resolve<ISpriteRenderer>();
	mSpriteRenderer->Initialize();
	printf("[GameLoop::Initialize] SpriteRenderer initalized\n");

	mInputManager = make_shared<InputManager>();
	IOCContainer::Instance().Register<IInputManager>(mInputManager);
	printf("[GameLoop::Initialize] InputManager registered\n");

	mSceneManager = make_shared<SceneManager>();
	IOCContainer::Instance().Register<ISceneManager>(mSceneManager);
	printf("[GameLoop::Initialize] SceneManager registered\n");

	mSceneManager->Initialize();
	printf("[GameLoop::Initialize] SceneManager initialized\n");

	// Game must register callback
	mGameLoopCallback = IOCContainer::Instance().Resolve<IGameLoopCallback>();
	mGameLoopCallback->Initialize();

	mIsInitialized = true;
}

GameLoop::~GameLoop() { }

void GameLoop::Tick() {
	if (!mIsInitialized)
		return;
	mTimer->Tick([&]() { 
		Update(); 
	});
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
	mInputManager->Update();
}

void GameLoop::Render() {
	if (!mIsInitialized)
		return;
	// Don't try to render anything before the first Update.
	if (mTimer->GetFrameCount() == 0) {
		return;
	}

	Clear();

	mSceneManager->Draw(mSpriteRenderer);
}

void GameLoop::Clear() const
{
	// TODO: Add your clearing code here
	mSpriteRenderer->Clear();
}
