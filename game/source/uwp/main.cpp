#include <Windows.h>
#include "IOC.hpp"
#include "game/Game.h"
#include <memory>

void StartUwpApplication();

int __cdecl main(Platform::Array<Platform::String^>^ args)
{
// int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
// {
	Utilities::IOCContainer::Instance().Register<Engine::IGameLoopCallback>(std::make_shared<Game>());
	StartUwpApplication();
	return 0;
}