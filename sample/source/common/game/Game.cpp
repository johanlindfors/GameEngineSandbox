#include "Game.h"
#include "utilities/IOC.hpp"
#include "scenes/ISceneManager.h"
#include "scenes/GenericScene.h"
#include "scenes/SimpleScene.h"

using namespace std;
using namespace Utilities;
using namespace Engine;
using namespace Sample;

void Game::initialize()
{
	auto sceneManager = IOCContainer::instance().resolve<ISceneManager>();
	//sceneManager->addScene(make_shared<GenericScene>());
	sceneManager->addScene(make_shared<SimpleScene>());
}
