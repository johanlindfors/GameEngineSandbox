#include <Windows.h>
#include "IOC.hpp"
#include "game/Game.h"
#include <memory>
#include <winrt/base.h>

void StartUwpApplication();

int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
	winrt::init_apartment();

	Utilities::IOCContainer::Instance().Register<Engine::IGameLoopCallback>(std::make_shared<Game>());
	StartUwpApplication();
	return 0;
}