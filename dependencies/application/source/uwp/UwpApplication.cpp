#include "UwpApplication.h"
#include <winrt/Windows.UI.Xaml.Controls.h>
#include "OpenGLES.h"
#include "GLPage.h"
#include "IDispatcherWrapper.h"
#include "IOC.hpp"

using namespace std;
using namespace winrt;
using namespace Windows::UI;
using namespace Windows::UI::Xaml;
using namespace Windows::ApplicationModel::Activation;
using namespace Engine;
using namespace Utilities;

void UwpApplication::OnLaunched(LaunchActivatedEventArgs const &)
{
	auto window = Window::Current();
	auto dispatcherWrapper = make_shared<DispatcherWrapper>(window.Dispatcher());
	IOCContainer::Instance().Register<IDispatcherWrapper>(dispatcherWrapper);
	
	auto glPage = make<GLPage>(make_shared<OpenGLES>());
	window.Content(glPage);
	window.Activate();
}
