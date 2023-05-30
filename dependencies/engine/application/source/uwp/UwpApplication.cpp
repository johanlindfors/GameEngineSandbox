#include "UwpApplication.hpp"
#include <winrt/Windows.UI.Xaml.Controls.h>
#include "OpenGLES.hpp"
#include "GLPage.hpp"
#include "DispatcherWrapper.hpp"
#include "utilities/IOC.hpp"

using namespace std;
using namespace winrt;
using namespace Windows::UI;
using namespace Windows::UI::Xaml;
using namespace Windows::ApplicationModel::Activation;
using namespace Engine;
using namespace Utilities;

void UwpApplication::OnLaunched(LaunchActivatedEventArgs const &)
{
	const auto window = Window::Current();
	auto dispatcher = window.Dispatcher();
	const auto dispatcherWrapper = make_shared<DispatcherWrapper>(dispatcher);
	IOCContainer::Instance().Register<IDispatcherWrapper>(dispatcherWrapper);

	auto openGLES = make_shared<OpenGLES>();
	const auto glPage = make<GLPage>(openGLES);
	window.Content(glPage);
	window.Activate();
}
