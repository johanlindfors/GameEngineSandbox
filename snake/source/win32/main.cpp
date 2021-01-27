#include <Windows.h>
#include <iostream>
#include "IOC.hpp"
#include "game/Game.h"
#include "application/Config.h"

void StartWin32Application();

int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR, int) {
  auto config = std::make_shared<Engine::Config>();
  config->FPS = 15;
  Utilities::IOCContainer::Instance().Register<Engine::Config>(config);
  Utilities::IOCContainer::Instance().Register<Engine::IGameLoopCallback>(std::make_shared<Game>());
  
  StartWin32Application();
  
  return 0;
}
