#include "Game.h"
#include "IOC.hpp"
#include "scenes/SceneManager.h"
#include "scenes/SplashScene.h"

using namespace std;
using namespace Utilities;
using namespace Engine;

void Game::Initialize()
{
	// Initialize
	mSceneManager = make_shared<SceneManager>();
	IOCContainer::Instance().Register<ISceneManager>(mSceneManager);
	mSceneManager->Initialize();

	mSceneManager->AddScene(make_shared<SplashScene>());
}

void Game::UpdateScreenSize(int width, int height)
{
    mSceneManager->UpdateScreenSize(width, height);
}

void Game::Update(shared_ptr<IStepTimer> timer)
{
	mSceneManager->Update(timer);
}

void Game::Draw(shared_ptr<IStepTimer> timer)
{
   	mSceneManager->Draw(timer);
}