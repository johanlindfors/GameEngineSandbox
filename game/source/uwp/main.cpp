#include "UwpApplication.h"
#include <Windows.h>
#include "IOC.hpp"
#include "scenes/SplashScene.h"
#include <memory>

#include <winrt/Windows.UI.Xaml.h>

using namespace winrt;
using Windows::UI::Xaml::Application;

int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR, int) {
	
	Application::Start([](auto &&) {
		auto initialScene = std::make_shared<SplashScene>();
		IOCContainer::Instance().Register<Engine::GameScene>(initialScene);
		make<Engine::UwpApplication>();
	});
	return 0;
}