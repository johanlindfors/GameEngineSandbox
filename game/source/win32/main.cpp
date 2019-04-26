#include <Windows.h>
#include <iostream>
#include "IOC.hpp"
#include "Game.h"

void StartWin32Application();

int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR, int) {
  Utilities::IOCContainer::Instance().Register<Engine::IGameLoopCallback>(std::make_shared<Game>());
  StartWin32Application();
  return 0;
}
