#include <Windows.h>
#include "game/Bootstrap.hpp"

void startWin32Application();

int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
  bootstrap();
  startWin32Application();
  return 0; /* ANSI C requires main to return int. */
}