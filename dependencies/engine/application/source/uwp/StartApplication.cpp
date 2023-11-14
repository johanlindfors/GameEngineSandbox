#include "UwpApplication.hpp"
#include <winrt/Windows.UI.Xaml.h>

using namespace winrt;
using namespace Windows::UI::Xaml;

void startApplication()
{
	Application::Start([](auto &&)
					   { make<Engine::UwpApplication>(); });
}