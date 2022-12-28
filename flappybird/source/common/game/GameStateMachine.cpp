#include "GameStateMachine.h"
#include "utilities/IOC.hpp"
#include "scenes/SplashScene.h"
#include "scenes/GamePlayScene.h"
#include "scenes/GameOverScene.h"
#include "scenes/ISceneManager.h"
#include "scenes/InstructionsScene.h"

using namespace std;
using namespace Utilities;
using namespace Engine;

GameStateMachine::GameStateMachine()
	: mCurrentState(GameState::Unknown)
	, mNextState(GameState::Unknown) { }

void GameStateMachine::Initialize()
{
	mSceneManager = IOCContainer::Instance().Resolve<ISceneManager>();
}

void GameStateMachine::HandleUnknownState()
{
	if(mCurrentState == GameState::Unknown)
	{
		mNextState = GameState::Boot;
	}
}

void GameStateMachine::HandleBootState()
{
	if(mCurrentState == GameState::Unknown)
	{
		mCurrentState = GameState::Boot;
		mNextState = GameState::Splash;
	}
}

void GameStateMachine::HandleSplashState()
{
	if(mCurrentState == GameState::Boot)
	{
		mCurrentState = GameState::Splash;
		mSceneManager->AddScene(make_shared<SplashScene>(this));
	}
}

void GameStateMachine::HandleInstructionsState()
{
	switch (mCurrentState)
	{
		case GameState::Splash:
			mSceneManager->AddScene(make_shared<GamePlayScene>(this));
			mSceneManager->AddScene(make_shared<InstructionsScene>(this));
			mSceneManager->RemoveScene(typeid(SplashScene));
			break;
		case GameState::GameOver:
			mSceneManager->AddScene(make_shared<InstructionsScene>(this));
			mSceneManager->RemoveScene(typeid(GameOverScene));
			break;
		default:
			break;
	}
	mCurrentState = GameState::Instructions;
}

void GameStateMachine::HandleGamePlayState()
{
	switch (mCurrentState)
	{
		case GameState::Instructions:
			mSceneManager->RemoveScene(typeid(InstructionsScene));
			break;
		default:
			break;
	}
	mCurrentState = GameState::GamePlay;
}

void GameStateMachine::HandleGameOverState()
{
	if (mCurrentState == GameState::GamePlay) {
		mCurrentState = GameState::GameOver;
		mSceneManager->AddScene(make_shared<GameOverScene>(this));
	}
}

void GameStateMachine::Update(shared_ptr<IStepTimer> timer)
{
	switch (mNextState)
	{
	case GameState::Unknown:
		HandleUnknownState();
		break;

	case GameState::Boot:
		HandleBootState();
		break;

	case GameState::Splash:
		HandleSplashState();
		break;

	case GameState::Instructions:
		HandleInstructionsState();
		break;

	case GameState::GamePlay:
		HandleGamePlayState();
		break;

	case GameState::GameOver:
		HandleGameOverState();
		break;

	case GameState::Loading:
	default:
		break;
	}
}

void GameStateMachine::GoToState(GameState gameState)
{
	mNextState = gameState;
}