#include "Game.hpp"
// Engine
#include "utilities/IOC.hpp"
// Game
#include "scenes/SplashScene.hpp"
#include "scenes/GamePlayScene.hpp"
#include "scenes/GameOverScene.hpp"
#include "scenes/PauseScene.hpp"
#include "scenes/ISceneManager.hpp"
#ifdef EMSCRIPTEN
#include "BootScene.hpp"
#endif

using namespace std;
using namespace Utilities;
using namespace Engine;

Game::Game()
	: mCurrentState(GameState::Unknown), mNextState(GameState::Unknown) {}

void Game::initialize()
{
	mSceneManager = IOCContainer::instance().resolve<ISceneManager>();
}

void Game::handleUnknownState()
{
	if (mCurrentState == GameState::Unknown)
	{
		mNextState = GameState::Boot;
	}
}

void Game::handleBootState()
{
	if (mCurrentState == GameState::Unknown)
	{
#ifdef EMSCRIPTEN
		mCurrentState = GameState::Boot;
		mSceneManager->addScene(make_shared<BootScene>(this));
#else
		mCurrentState = GameState::Boot;
		mNextState = GameState::Splash;
#endif
	}
}

void Game::handleSplashState()
{
	if (mCurrentState == GameState::Boot)
	{
		mCurrentState = GameState::Splash;
		mSceneManager->addScene(make_shared<SplashScene>(this));
	}
}

void Game::handleGamePlayState()
{
	switch (mCurrentState)
	{
	case GameState::Splash:
		mSceneManager->addScene(make_shared<GamePlayScene>(this));
		mSceneManager->removeScene(typeid(SplashScene));
		break;
	case GameState::GameOver:
		mSceneManager->addScene(make_shared<GamePlayScene>(this));
		mSceneManager->removeScene(typeid(GameOverScene));
		break;
	case GameState::Pause:
		mSceneManager->removeScene(typeid(PauseScene));
		break;
	default:
		break;
	}
	mCurrentState = GameState::GamePlay;
}

void Game::handleGameOverState()
{
	if (mCurrentState == GameState::GamePlay)
	{
		mCurrentState = GameState::GameOver;
		mSceneManager->addScene(make_shared<GameOverScene>(this));
		mSceneManager->removeScene(typeid(GamePlayScene));
	}
}

void Game::handlePauseState()
{
	if (mCurrentState == GameState::GamePlay)
	{
		mCurrentState = GameState::Pause;
		mSceneManager->addScene(make_shared<PauseScene>());
	}
}

void Game::update(shared_ptr<IStepTimer> timer)
{
	switch (mNextState)
	{
	case GameState::Unknown:
		handleUnknownState();
		break;

	case GameState::Boot:
		handleBootState();
		break;

	case GameState::Splash:
		handleSplashState();
		break;

	case GameState::GamePlay:
		handleGamePlayState();
		break;

	case GameState::GameOver:
		handleGameOverState();
		break;

	case GameState::Pause:
		handlePauseState();
		break;

	case GameState::Menu:
	case GameState::Loading:
	default:
		break;
	}
}

void Game::goToState(GameState gameState)
{
	mNextState = gameState;
}
