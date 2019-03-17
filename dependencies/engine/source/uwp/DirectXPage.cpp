#include "DirectXPage.h"

using namespace Engine;
using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::UI;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Media;

DirectXPage::DirectXPage() 
{
   	TextBlock block;

	//block.FontFamily(FontFamily(L"Segoe UI Semibold"));
	block.FontSize(72.0);
	block.Foreground(SolidColorBrush(Colors::Orange()));
	block.VerticalAlignment(VerticalAlignment::Center);
	block.TextAlignment(TextAlignment::Center);
	block.TextWrapping(TextWrapping::Wrap);
	block.Text(L"Game Engine Sandbox");

    Content(block);
}