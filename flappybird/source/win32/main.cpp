#include <Windows.h>
#include <iostream>
#include "game/Bootstrap.hpp"

void StartWin32Application();

int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR, int) {
  Bootstrap();
  
  StartWin32Application();
  
  return 0;
}
