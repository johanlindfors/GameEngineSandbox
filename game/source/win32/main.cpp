#include <Windows.h>
#include <iostream>
#include <test.h>
#include "IOC.hpp"
#include "scenes/SplashScene.h"

void StartWin32Application();

int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR, int) {
  IOCContainer::Instance().Register<GameScene>(std::make_shared<SplashScene>());  
  StartWin32Application();
  return 0;
}