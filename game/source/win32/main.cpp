#include <Windows.h>
#include <iostream>
#include <test.h>

void StartWin32Application();

int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR, int) {
  StartWin32Application();
  return 0;
}