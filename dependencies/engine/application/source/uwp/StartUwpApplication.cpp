#include "UwpApplication.hpp"
#include <winrt/Windows.UI.Xaml.h>

using namespace winrt;
using namespace Windows::UI::Xaml;

void StartUwpApplication() 
{
   	Application::Start([](auto &&) {
  		make<Engine::UwpApplication>();
	});
}