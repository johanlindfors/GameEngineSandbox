#include "Game.h"
#include "utilities/IOC.hpp"
#include "scenes/ISceneManager.h"
#include "scenes/GenericScene.h"

using namespace std;
using namespace Utilities;
using namespace Engine;
using namespace Sample;

Game::~Game() 
{
	printf("[Game::~Game]\n");
}

void Game::Initialize()
{
	auto sceneManager = IOCContainer::Instance().Resolve<ISceneManager>();
	sceneManager->AddScene(make_shared<GenericScene>());
}
