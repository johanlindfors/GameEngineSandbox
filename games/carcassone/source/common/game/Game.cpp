#include "Game.hpp"
#include "utilities/IOC.hpp"
#include "scenes/ISceneManager.hpp"
#include "scenes/SpriteScene.hpp"

using namespace std;
using namespace Utilities;
using namespace Engine;
using namespace Sample;

void Game::initialize()
{
	auto sceneManager = IOCContainer::instance().resolve<ISceneManager>();
	sceneManager->addScene(make_shared<SpriteScene>());
}
