#include <Windows.h>
#include "IOC.hpp"
#include "game/Game.h"
#include <memory>
#include <winrt/base.h>
#include "application/Config.h"

void StartUwpApplication();

int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
	winrt::init_apartment();

	const auto config = std::make_shared<Engine::Config>();
	config->FPS = 15;
	Utilities::IOCContainer::Instance().Register<Engine::Config>(config);
	Utilities::IOCContainer::Instance().Register<Engine::IGameLoopCallback>(std::make_shared<Game>());
	
	StartUwpApplication();
	
	return 0;
}