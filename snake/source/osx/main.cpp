#include "IOC.hpp"
#include "game/Game.h"
#include "application/Config.h"

void StartOsxApplication(int argc, char** argv);

int
main(int argc, char **argv)
{
  auto config = std::make_shared<Engine::Config>();
  config->FPS = 15;
  Utilities::IOCContainer::Instance().Register<Engine::Config>(config);
  Utilities::IOCContainer::Instance().Register<Engine::IGameLoopCallback>(std::make_shared<Game>());

  StartOsxApplication(argc, argv);
  return 0;             /* ANSI C requires main to return int. */
}