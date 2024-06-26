#include "Game.hpp"
#include "utilities/IOC.hpp"
#include "scenes/ISceneManager.hpp"
#include "scenes/SpriteScene.hpp"
#ifdef __EMSCRIPTEN__
#include "utilities/Logger.hpp"
#include "emscripten/BootScene.hpp"
#endif

using namespace std;
using namespace Utilities;
using namespace Engine;
using namespace Sample;

void Game::initialize()
{
	auto sceneManager = IOCContainer::instance().resolve<ISceneManager>();
	//sceneManager->addScene(make_shared<ModelScene>());
#ifdef __EMSCRIPTEN__
	debuglog << "[Game::initialize] Adding BootScene" << endl;
	sceneManager->addScene(make_shared<BootScene>());
#else
	sceneManager->addScene(make_shared<SpriteScene>());
#endif
}
