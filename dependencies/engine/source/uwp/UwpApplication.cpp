#include "UwpApplication.h"
#include <winrt/Windows.UI.Xaml.Controls.h>
#include <winrt/Windows.UI.Xaml.Media.h>
#include <winrt/Windows.Foundation.h>
#include "DirectXPage.h"

using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::UI;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Media;

UwpApplication::UwpApplication(IPlatformProxy* platformProxy)
	: mPlatformProxy(platformProxy)
{

}

void UwpApplication::OnLaunched(LaunchActivatedEventArgs const &)
{
	auto page = winrt::make<Engine::DirectXPage>();

	Window window = Window::Current();
	window.Content(page);
	window.Activate();
}
