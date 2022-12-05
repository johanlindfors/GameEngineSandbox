#include "Game.h"
#include "utilities/IOC.hpp"
#include "scenes/SplashScene.h"
#include "scenes/GamePlayScene.h"
#include "scenes/GameOverScene.h"
#include "scenes/PauseScene.h"
#include "scenes/ISceneManager.h"

using namespace std;
using namespace Utilities;
using namespace Engine;

Game::Game()
	: mCurrentState(GameState::Unknown)
	, mNextState(GameState::Unknown) { }

void Game::Initialize()
{
	mSceneManager = IOCContainer::Instance().Resolve<ISceneManager>();
}

void Game::HandleUnknownState()
{
	if(mCurrentState == GameState::Unknown)
	{
		mNextState = GameState::Boot;
	}
}

void Game::HandleBootState()
{
	if(mCurrentState == GameState::Unknown)
	{
		mCurrentState = GameState::Boot;
		mNextState = GameState::Splash;
	}
}

void Game::HandleSplashState()
{
	if(mCurrentState == GameState::Boot)
	{
		mCurrentState = GameState::Splash;
		mSceneManager->AddScene(make_shared<SplashScene>(this));
	}
}

void Game::HandleGamePlayState()
{
	switch (mCurrentState)
	{
		case GameState::Splash:
			mSceneManager->AddScene(make_shared<GamePlayScene>(this));
			mSceneManager->RemoveScene(typeid(SplashScene));
			break;
		case GameState::GameOver:
			//mSceneManager->AddScene(make_shared<GamePlayScene>(this));
			mSceneManager->RemoveScene(typeid(GameOverScene));
			break;
		case GameState::Pause:
			mSceneManager->RemoveScene(typeid(PauseScene));
			break;
		default:
			break;
	}
	mCurrentState = GameState::GamePlay;
}

void Game::HandleGameOverState()
{
	if (mCurrentState == GameState::GamePlay) {
		mCurrentState = GameState::GameOver;
		mSceneManager->AddScene(make_shared<GameOverScene>(this));
		//mSceneManager->RemoveScene(typeid(GamePlayScene));
	}
}

void Game::HandlePauseState()
{
	if (mCurrentState == GameState::GamePlay) {
		mCurrentState = GameState::Pause;
		mSceneManager->AddScene(make_shared<PauseScene>());
	}
}

void Game::Update(shared_ptr<IStepTimer> timer)
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

	case GameState::GamePlay:
		HandleGamePlayState();
		break;

	case GameState::GameOver:
		HandleGameOverState();
		break;

	case GameState::Pause:
		HandlePauseState();
		break;

	case GameState::Menu:
	case GameState::Loading:
	default:
		break;
	}
}

void Game::GoToState(GameState gameState)
{
	mNextState = gameState;
}