#include "GameStateMachine.hpp"

// engine
#include "utilities/IOC.hpp"

// game
#include "scenes/BootScene.hpp"
#include "scenes/GamePlayScene.hpp"
#include "scenes/GameOverScene.hpp"
#include "scenes/ISceneManager.hpp"

using namespace std;
using namespace Engine;
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
		mSceneManager->addScene(make_shared<BootScene>(this));
	}
	mCurrentState = GameState::Boot;
}

void GameStateMachine::handleGamePlayState()
{
	switch (mCurrentState)
	{
	case GameState::Boot:
		mSceneManager->removeScene(typeid(BootScene));
		mSceneManager->addScene(make_shared<GamePlayScene>(this));
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
		mSceneManager->removeScene(typeid(GamePlayScene));
		mSceneManager->addScene(make_shared<GameOverScene>(this));
	}
	mCurrentState = GameState::GameOver;
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

	case GameState::GamePlay:
		handleGamePlayState();
		break;

	case GameState::GameOver:
		handleGameOverState();
		break;
	}
}

void GameStateMachine::goToState(GameState gameState)
{
	mNextState = gameState;
}
