#include "UwpApplication.h"
#include <Windows.h>

#include <winrt/Windows.UI.Xaml.h>

using namespace winrt;
using Windows::UI::Xaml::Application;

int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR, int) {
  Application::Start([](auto &&) { make<UwpApplication>(); });
  return 0;
}