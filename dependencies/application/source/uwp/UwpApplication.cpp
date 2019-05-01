#include "UwpApplication.h"
#include <winrt/Windows.UI.Xaml.Controls.h>
#include "OpenGLES.h"
#include "GLPage.h"
#include "DispatcherWrapper.h"
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
	auto window = Windows::Current();
	auto dispatcher = window.Dispatcher();
	auto dispatcherWrapper = make_shared<DispatcherWrapper>(dispatcher);
	IOCContainer::Instance().Register<IDispatcherWrapper>(dispatcherWrapper);
	
	auto openGLES = make_shared<OpenGLES>();
	auto glPage = make<GLPage>(openGLES);
	window.Content(glPage);
	window.Activate();
}
