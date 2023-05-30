#include "UwpApplication.hpp"

using namespace Windows::UI::Xaml;

void StartUwpApplication() 
{
   	Application::Start(ref new ApplicationInitializationCallback([](ApplicationInitializationCallbackParams ^ p) {
  		auto app = ref new Engine::UwpApplication();
	}));
}