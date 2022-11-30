#include <iostream>
#include "IOC.hpp"
#include "game/Game.h"
#include "application/Config.h"
#include "game/GameDefines.h"
#include "physics/PhysicsEngine.h"

void StartLinuxApplication(int argc, char **argv);

int main(int argc, char **argv)
{
    setbuf(stdout, NULL);
    auto config = std::make_shared<Engine::Config>();
    config->FPS = 60;
    config->Width = SCREEN_WIDTH;
    config->Height = SCREEN_HEIGHT;
    config->Title = "Flappy Bird";
    Utilities::IOCContainer::Instance().Register<Engine::IPhysicsEngine>(std::make_shared<Engine::PhysicsEngine>());
    Utilities::IOCContainer::Instance().Register<Engine::Config>(config);
    Utilities::IOCContainer::Instance().Register<Engine::IGameLoopCallback>(std::make_shared<Game>());

    StartLinuxApplication(argc, argv);
  
    return 0;
}
