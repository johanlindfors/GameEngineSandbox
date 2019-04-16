#include "UwpApplication.h"
#include <Windows.h>
#include "IOC.hpp"
#include "scenes/SplashScene.h"
#include "scenes/SceneManager.h"
#include <memory>

#include <winrt/Windows.UI.Xaml.h>

using namespace winrt;
using Windows::UI::Xaml::Application;

int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR, int) {
  auto sceneManager = std::make_shared<SceneManager>();
  sceneManager->AddScene(new SplashScene());
  IOCContainer::Instance().Register<ISceneManager>(sceneManager);

  Application::Start([](auto &&) { make<UwpApplication>(); });
  return 0;
}