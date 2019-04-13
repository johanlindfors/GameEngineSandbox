#include "UwpApplication.h"
#include <Windows.h>
#include "IOC.hpp"
#include "scenes/SplashScene.h"

#include <winrt/Windows.UI.Xaml.h>

using namespace winrt;
using Windows::UI::Xaml::Application;

int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR, int) {
  IOCContainer::Instance().Register<GameScene>(std::make_shared<SplashScene>());
  Application::Start([](auto &&) { make<UwpApplication>(); });
  return 0;
}