#include "game-loop/GameLoop.hpp"
#include "utilities/IOC.hpp"
#include "utilities/Config.hpp"
#include "scenes/SceneManager.hpp"
#include "input/InputManager.hpp"
#include "resources/ResourceManager.hpp"
#include "renderers/ISpriteRenderer.hpp"
#include "utilities/StepTimer.hpp"
#include "game-loop/IGameLoopCallback.hpp"
#include "filesystem/FileSystem.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;

GameLoop::GameLoop() 
	: mIsInitialized(false) { }

void GameLoop::initialize(shared_ptr<Config> config) {
	mTimer = make_shared<StepTimer>();
	mTimer->setFixedTimeStep(config->useFixedTimeStep);
	mTimer->setTargetElapsedSeconds(1.0f/config->fps);

    printf("[GameLoop::initialize] Timer initialized\n");

	// Ordering is important
	if(!IOCContainer::instance().contains<FileSystem>()){
		mFileSystem = make_shared<FileSystem>();
		IOCContainer::instance().register_type<IFileSystem>(mFileSystem);
		printf("[GameLoop::initialize] FileSystem registered\n");
	}
	
	if(!IOCContainer::instance().contains<IResourceManager>()){
		mResourceManager = make_shared<ResourceManager>();
		IOCContainer::instance().register_type<IResourceManager>(mResourceManager);
		printf("[GameLoop::initialize] ResourceManager registered\n");
	}

	if(IOCContainer::instance().contains<IRenderer>()){
		mRenderer = IOCContainer::instance().resolve<IRenderer>();
		mRenderer->initialize();
		printf("[GameLoop::initialize] Renderer initalized\n");
	}

	mInputManager = make_shared<InputManager>();
	IOCContainer::instance().register_type<IInputManager>(mInputManager);
	printf("[GameLoop::initialize] InputManager registered\n");

	mSceneManager = make_shared<SceneManager>();
	IOCContainer::instance().register_type<ISceneManager>(mSceneManager);
	printf("[GameLoop::initialize] SceneManager registered\n");

	mSceneManager->initialize();
	printf("[GameLoop::initialize] SceneManager initialized\n");

	// Game must register callback
	mGameLoopCallback = IOCContainer::instance().resolve<IGameLoopCallback>();
	mGameLoopCallback->initialize();

	mIsInitialized = true;
}

GameLoop::~GameLoop() {
	printf("[GameLoop::~GameLoop]\n");
	mTimer.reset();

	mSceneManager.reset();
	mInputManager.reset();
	if(mResourceManager.get())
		mResourceManager.reset();
	if(mFileSystem.get())
		mFileSystem.reset();
}

void GameLoop::tick() {
	if (!mIsInitialized)
		return;
	mTimer->tick(
		[&]() { /* process input*/ },
		[&]() { update(); },
		[&]() { render(); }
	);
}

void GameLoop::updateWindowSize(int width, int height)
{
	// TODO: Handle window size changed events
	if (!mIsInitialized)
		return;
	if(!mRenderer) {
		if(IOCContainer::instance().contains<IRenderer>()){
			mRenderer = IOCContainer::instance().resolve<IRenderer>();
		}
	}
	if(mRenderer) {
		mRenderer->updateWindowSize(width, height);
	}
	mSceneManager->updateScreenSize(width, height);
}

void GameLoop::getDefaultSize(int &width, int &height)
{
	// TODO: Change to desired default window size (note minimum size is 320x200).
	width = 500;
	height = 500;
}

void GameLoop::update() const
{
	if (!mIsInitialized)
		return;

	// TODO: Add your game logic here.
	mGameLoopCallback->update(mTimer);	
	mSceneManager->update(mTimer);
	mInputManager->update();
}

void GameLoop::render() {
	if (!mIsInitialized)
		return;
	// Don't try to render anything before the first Update.
	if (mTimer->getFrameCount() == 0) {
		return;
	}
	if(!mRenderer) {
		if(IOCContainer::instance().contains<IRenderer>()){
			mRenderer = IOCContainer::instance().resolve<IRenderer>();
		}
	}
	clear();
	mSceneManager->draw(mRenderer);
}

void GameLoop::clear() const
{
	if(mRenderer) {
		mRenderer->clear();
	}
}
