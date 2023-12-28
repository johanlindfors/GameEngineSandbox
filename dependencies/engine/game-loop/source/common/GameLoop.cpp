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
#include "utilities/Logger.hpp"
#include "renderers/FrameBufferRenderer.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;

GameLoop::GameLoop()
	: mIsInitialized(false) {}

void GameLoop::initialize(shared_ptr<Config> config)
{
	mTimer = make_shared<StepTimer>();
	mTimer->setFixedTimeStep(config->useFixedTimeStep);
	mTimer->setTargetElapsedSeconds(1.0f / config->fps);

    debuglog << "[GameLoop::initialize] Timer initialized" << std::endl;

	// Ordering is important
	if (!IOCContainer::instance().contains<FileSystem>())
	{
		mFileSystem = make_shared<FileSystem>();
		IOCContainer::instance().register_type<IFileSystem>(mFileSystem);
		debuglog << "[GameLoop::initialize] FileSystem registered" << std::endl;
	}

	if (!IOCContainer::instance().contains<IResourceManager>())
	{
		mResourceManager = make_shared<ResourceManager>();
		IOCContainer::instance().register_type<IResourceManager>(mResourceManager);
		debuglog << "[GameLoop::initialize] ResourceManager registered" << std::endl;
	}

	if (IOCContainer::instance().contains<IRenderer>())
	{
		mRenderer = IOCContainer::instance().resolve<IRenderer>();
		mRenderer->initialize();
		debuglog << "[GameLoop::initialize] Renderer initalized" << std::endl;
	}

	if(config->useFixedGameSize) {
		// framebuffer prepare
		if (IOCContainer::instance().contains<FrameBufferRenderer>()) {
			mFrameBufferRenderer = IOCContainer::instance().resolve<FrameBufferRenderer>();
		} else {
			mResourceManager->loadShader( "framebuffer", "framebuffer.vs", "framebuffer.fs" );
			mFrameBufferRenderer = make_shared<FrameBufferRenderer>();
			mFrameBufferRenderer->initialize(config, mResourceManager->getShader("framebuffer"));
		}
	}


	mInputManager = make_shared<InputManager>();
	IOCContainer::instance().register_type<IInputManager>(mInputManager);
	debuglog << "[GameLoop::initialize] InputManager registered" << std::endl;

	mSceneManager = make_shared<SceneManager>();
	IOCContainer::instance().register_type<ISceneManager>(mSceneManager);
	debuglog << "[GameLoop::initialize] SceneManager registered" << std::endl;

	mSceneManager->initialize();
	debuglog << "[GameLoop::initialize] SceneManager initialized" << std::endl;

	// Game must register callback
	mGameLoopCallback = IOCContainer::instance().resolve<IGameLoopCallback>();
	mGameLoopCallback->initialize();

	mIsInitialized = true;
}

GameLoop::~GameLoop() {
	debuglog << "[GameLoop::~GameLoop]" << std::endl;
	mTimer.reset();

	mSceneManager.reset();
	mInputManager.reset();
	if (mResourceManager.get())
		mResourceManager.reset();
	if (mFileSystem.get())
		mFileSystem.reset();
}

void GameLoop::tick()
{
	if (!mIsInitialized)
		return;
	mTimer->tick(
		[&]() { handleInput(); },
		[&]() { update(); },
		[&]() { render(); }
	);
}

void GameLoop::updateWindowSize(int width, int height)
{
	// TODO: Handle window size changed events
	if (!mIsInitialized)
		return;
	if (!mRenderer)
	{
		if (IOCContainer::instance().contains<IRenderer>())
		{
			mRenderer = IOCContainer::instance().resolve<IRenderer>();
		}
	}
	if (mRenderer)
	{
		mRenderer->updateWindowSize(width, height);
	}
	mSceneManager->updateScreenSize(width, height);
	if(mFrameBufferRenderer)
	{
		mFrameBufferRenderer->updateScreenSize(width, height);
	}
}

void GameLoop::getDefaultSize(int &width, int &height)
{
	// TODO: Change to desired default window size (note minimum size is 320x200).
	width = 500;
	height = 500;
}

void GameLoop::handleInput() const 
{
	mInputManager->update();
}

void GameLoop::update() const
{
	// TODO: Add your game logic here.
	mGameLoopCallback->update(mTimer);
	mSceneManager->update(mTimer);
}

void GameLoop::render()
{
	// Don't try to render anything before the first Update.
	if (mTimer->getFrameCount() == 0)
		return;

	if (!mRenderer)
	{
		if (IOCContainer::instance().contains<IRenderer>())
		{
			mRenderer = IOCContainer::instance().resolve<IRenderer>();
		}
	}
	if (mRenderer)
	{
		if(mFrameBufferRenderer)
			mFrameBufferRenderer->begin();
	
		mSceneManager->draw(mRenderer);
	
		if(mFrameBufferRenderer)
			mFrameBufferRenderer->end();
	}
}
