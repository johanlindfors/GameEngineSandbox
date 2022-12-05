#include <iostream>
#include "utilities/IOC.hpp"
#include "game/Game.h"
#include "application/Config.h"
#include "game/GameDefines.h"
#include "physics/PhysicsEngine.h"
#include "physics/ObjectCollider.h"
#include "utilities/TweenEngine.h"

using namespace std;
using namespace Engine;
using namespace Utilities;

void StartLinuxApplication(int argc, char **argv);

int main(int argc, char **argv)
{
    setbuf(stdout, NULL);
    auto config = make_shared<Config>();
    config->FPS = 60;
    config->Width = SCREEN_WIDTH;
    config->Height = SCREEN_HEIGHT;
    config->Title = "Flappy Bird";
    IOCContainer::Instance().Register<IPhysicsEngine>(make_shared<PhysicsEngine>());
    IOCContainer::Instance().Register<IObjectCollider>(make_shared<ObjectCollider>());
    IOCContainer::Instance().Register<ITweenEngine>(make_shared<TweenEngine>());

    IOCContainer::Instance().Register<Config>(config);
    IOCContainer::Instance().Register<IGameLoopCallback>(make_shared<Game>());

    StartLinuxApplication(argc, argv);
  
    return 0;
}
