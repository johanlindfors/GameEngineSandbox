#include "Game.hpp"
#include <memory>
#include "utilities/IOC.hpp"
#include "scenes/ISceneManager.hpp"
#if EMSCRIPTEN
#include "scenes/BootScene.hpp"
#else
#include "scenes/SpriteScene.hpp"
#endif

using namespace std;
using namespace Utilities;
using namespace Engine;
using namespace HelloWorld::Scenes;

void Game::initialize()
{
    IOCContainer::instance()
        .resolve<ISceneManager>()
#if EMSCRIPTEN
        ->addScene(make_shared<BootScene>());
#else
        ->addScene(make_shared<SpriteScene>());
#endif
}
