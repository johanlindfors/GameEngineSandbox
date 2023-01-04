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

void Game::initialize()
{
	auto sceneManager = IOCContainer::instance().resolve<ISceneManager>();
	sceneManager->addScene(make_shared<GenericScene>());
}
