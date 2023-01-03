#include "GameStateMachine.h"
#include "utilities/IOC.hpp"
#include "scenes/ISceneManager.h"
#include "scenes/RenderingScene.h"
#include "scenes/GenericScene.h"

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
		mNextState = GameState::Rendering;
	}
}

void GameStateMachine::HandleRenderingState()
{
	switch (mCurrentState)
	{
		case GameState::Unknown:
			mSceneManager->AddScene(make_shared<Sample::GenericScene>(this));
			break;
		default:
			break;
	}
	mCurrentState = GameState::Rendering;
}

void GameStateMachine::Update(shared_ptr<IStepTimer> timer)
{
	switch (mNextState)
	{
	case GameState::Unknown:
		HandleUnknownState();
		break;

	case GameState::Rendering:
		HandleRenderingState();
		break;

	default:
		break;
	}
}

void GameStateMachine::GoToState(GameState gameState)
{
	mNextState = gameState;
}