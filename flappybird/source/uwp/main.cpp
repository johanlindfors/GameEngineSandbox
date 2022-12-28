#include <Windows.h>
#include "game/Bootstrap.hpp"
#include <winrt/base.h>

void StartUwpApplication();

int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
	winrt::init_apartment();

	Bootstrap();
	
	StartUwpApplication();
	
	return 0;
}