#include "Game.h"
#include "utilities/IOC.hpp"
#include "scenes/ISceneManager.h"
#include "scenes/SpriteScene.h"
#include "scenes/ModelScene.h"

using namespace std;
using namespace Utilities;
using namespace Engine;
using namespace Sample;

void Game::initialize()
{
	auto sceneManager = IOCContainer::instance().resolve<ISceneManager>();
	//sceneManager->addScene(make_shared<ModelScene>());
	sceneManager->addScene(make_shared<SpriteScene>());
}
