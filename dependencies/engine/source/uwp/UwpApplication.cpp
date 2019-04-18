#include "UwpApplication.h"
#include <winrt/Windows.UI.Xaml.Controls.h>
#include <winrt/Windows.UI.Xaml.Media.h>
#include <winrt/Windows.Foundation.h>
#include "OpenGLES.h"
#include "GLPage.h"
#include "DispatcherWrapper.h"
#include "IOC.hpp"

using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::UI;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Media;
using namespace Engine;
using namespace Utilities;

UwpApplication::UwpApplication()
{

}

void UwpApplication::OnLaunched(LaunchActivatedEventArgs const &)
{
	auto glPage = winrt::make<Engine::GLPage>(std::make_shared<OpenGLES>());

	Window window = Window::Current();
	auto dispatcherWrapper = std::make_shared<DispatcherWrapper>(window.Dispatcher());
	IOCContainer::Instance().Register<DispatcherWrapper>(dispatcherWrapper);
	window.Content(glPage);
	window.Activate();
}
