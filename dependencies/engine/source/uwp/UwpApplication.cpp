#include "UwpApplication.h"
#include <winrt/Windows.UI.Xaml.Controls.h>
#include <winrt/Windows.UI.Xaml.Media.h>
#include <winrt/Windows.Foundation.h>

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
	TextBlock block;

	block.FontFamily(FontFamily(L"Segoe UI Semibold"));
	block.FontSize(72.0);
	block.Foreground(SolidColorBrush(Colors::Orange()));
	block.VerticalAlignment(VerticalAlignment::Center);
	block.TextAlignment(TextAlignment::Center);
	block.TextWrapping(TextWrapping::Wrap);
	block.Text(L"Game Engine Sandbox");

	Window window = Window::Current();
	window.Content(block);
	window.Activate();
}
