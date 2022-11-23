#include <iostream>
#include "IOC.hpp"
#include "game/Game.h"
#include "application/Config.h"

void StartLinuxApplication(int argc, char **argv);

int main(int argc, char **argv)
{
    setbuf(stdout, NULL);
    auto config = std::make_shared<Engine::Config>();
    config->Width = 500;
    config->Height = 500;
    config->FPS = 15;
    Utilities::IOCContainer::Instance().Register<Engine::Config>(config);
    Utilities::IOCContainer::Instance().Register<Engine::IGameLoopCallback>(std::make_shared<Game>());

    StartLinuxApplication(argc, argv);
  
    return 0;
}
