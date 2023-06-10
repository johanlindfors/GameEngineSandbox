#include "GameStateMachine.hpp"
#include "utilities/IOC.hpp"
#include "scenes/BootScene.hpp"
#include "scenes/GamePlayScene.hpp"
#include "scenes/GameOverScene.hpp"
#include "scenes/ISceneManager.hpp"

using namespace std;
using namespace Utilities;
using namespace Engine;

GameStateMachine::GameStateMachine()
	: mCurrentState(GameState::Unknown)
	, mNextState(GameState::Unknown) { }

void GameStateMachine::initialize()
{
	mSceneManager = IOCContainer::instance().resolve<ISceneManager>();
}

void GameStateMachine::handleUnknownState()
{
	if(mCurrentState == GameState::Unknown)
	{
		mNextState = GameState::Boot;
	}
}

void GameStateMachine::handleBootState()
{
	if(mCurrentState == GameState::Unknown)
	{
		mCurrentState = GameState::Boot;
		mNextState = GameState::GamePlay;
	}
}

void GameStateMachine::handleGamePlayState()
{
	// switch (mCurrentState)
	// {
	// 	case GameState::Instructions:
	// 		mSceneManager->removeScene(typeid(BootScene));
	// 		break;
	// 	default:
	// 		break;
	// }
	// mCurrentState = GameState::GamePlay;
}

void GameStateMachine::handleGameOverState()
{
	if (mCurrentState == GameState::GamePlay) {
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