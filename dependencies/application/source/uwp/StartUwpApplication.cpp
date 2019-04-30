#include "UwpApplication.h"
#include <winrt/Windows.UI.Xaml.h>

using namespace winrt;
using Windows::UI::Xaml::Application;

void StartUwpApplication() 
{
   	Application::Start([](auto &&) {
  		make<Engine::UwpApplication>();
	});
}