#pragma once
#include <winrt/Windows.UI.Xaml.Controls.h>
#include <winrt/Windows.UI.Xaml.Media.h>
#include <winrt/Windows.Foundation.h>

namespace Engine
{
    struct DirectXPage : winrt::Windows::UI::Xaml::Controls::PageT<DirectXPage> 
    {
        DirectXPage();
    };
}