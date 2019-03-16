#include <Windows.h>
#include "UwpApplication.h"

#include <winrt/Windows.UI.Xaml.h>

using winrt::Windows::UI::Xaml::Application;

int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
	Application::Start([](auto &&) { 
        winrt::make<UwpApplication>(); 
    });
    return 0;
}