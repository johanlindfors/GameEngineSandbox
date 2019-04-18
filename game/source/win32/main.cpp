#include <Windows.h>
#include <iostream>
#include "IOC.hpp"
#include "scenes/SplashScene.h"

void StartWin32Application();

int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR, int) {
  Utilities::IOCContainer::Instance().Register<Engine::GameScene>(std::make_shared<SplashScene>());  
  StartWin32Application();
  return 0;
}
