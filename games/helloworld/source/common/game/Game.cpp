#include "Game.hpp"
#include <memory>
#include "utilities/IOC.hpp"
#include "scenes/ISceneManager.hpp"
#include "scenes/BootScene.hpp"
#include "scenes/SpriteScene.hpp"

using namespace std;
using namespace Utilities;
using namespace Engine;
using namespace HelloWorld::Scenes;

void Game::initialize()
{
    IOCContainer::instance()
        .resolve<ISceneManager>()
        ->addScene(make_shared<BootScene>());
}
