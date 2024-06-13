#include "GameStateMachine.hpp"
#include "utilities/IOC.hpp"
#include "scenes/SplashScene.hpp"
#include "scenes/GamePlayScene.hpp"
#include "scenes/GameOverScene.hpp"
#include "scenes/ISceneManager.hpp"
#include "scenes/InstructionsScene.hpp"

#ifdef EMSCRIPTEN
#include "BootScene.hpp"
#endif

using namespace std;
using namespace Utilities;
using namespace Engine;

GameStateMachine::GameStateMachine()
	: mCurrentState(GameState::Unknown), mNextState(GameState::Unknown) {}

void GameStateMachine::initialize()
{
	mSceneManager = IOCContainer::instance().resolve<ISceneManager>();
}

void GameStateMachine::handleUnknownState()
{
	if (mCurrentState == GameState::Unknown)
	{
		mNextState = GameState::Boot;
	}
}

void GameStateMachine::handleBootState()
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

void GameStateMachine::handleSplashState()
{
	if (mCurrentState == GameState::Boot)
	{
		mCurrentState = GameState::Splash;
		mSceneManager->addScene(make_shared<SplashScene>(this));
#ifdef EMSCRIPTEN
		mSceneManager->removeScene(typeid(BootScene));
#endif
	}
}

void GameStateMachine::handleInstructionsState()
{
	switch (mCurrentState)
	{
	case GameState::Splash:
		mSceneManager->addScene(make_shared<GamePlayScene>(this));
		mSceneManager->addScene(make_shared<InstructionsScene>(this));
		mSceneManager->removeScene(typeid(SplashScene));
		break;
	case GameState::GameOver:
		mSceneManager->addScene(make_shared<InstructionsScene>(this));
		mSceneManager->removeScene(typeid(GameOverScene));
		break;
	default:
		break;
	}
	mCurrentState = GameState::Instructions;
}

void GameStateMachine::handleGamePlayState()
{
	switch (mCurrentState)
	{
	case GameState::Instructions:
		mSceneManager->removeScene(typeid(InstructionsScene));
		break;
	default:
		break;
	}
	mCurrentState = GameState::GamePlay;
}

void GameStateMachine::handleGameOverState()
{
	if (mCurrentState == GameState::GamePlay)
	{
		mCurrentState = GameState::GameOver;
		mSceneManager->addScene(make_shared<GameOverScene>(this));
	}
}

void GameStateMachine::update(shared_ptr<IStepTimer> timer)
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

	case GameState::Instructions:
		handleInstructionsState();
		break;

	case GameState::GamePlay:
		handleGamePlayState();
		break;

	case GameState::GameOver:
		handleGameOverState();
		break;

	case GameState::Loading:
	default:
		break;
	}
}

void GameStateMachine::goToState(GameState gameState)
{
	mNextState = gameState;
}