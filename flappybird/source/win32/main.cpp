#include <Windows.h>
#include <iostream>
#include "game/Bootstrap.hpp"

void startWin32Application();

int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	bootstrap();
	startWin32Application();
	return 0;
}
