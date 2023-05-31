#include <Windows.h>
#include "game/Bootstrap.hpp"

void startApplication();

int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
    bootstrap();
    startApplication();

    return 0;
}
