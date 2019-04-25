#include "UwpApplication.h"
#include <Windows.h>
#include "IOC.hpp"
#include "Game.h"
#include <memory>

#include <winrt/Windows.UI.Xaml.h>

using namespace winrt;
using Windows::UI::Xaml::Application;

int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR, int) {
	
	Application::Start([](auto &&) {
		Utilities::IOCContainer::Instance().Register<Engine::IGameLoopCallback>(std::make_shared<Game>());
  		make<Engine::UwpApplication>();
	});
	return 0;
}