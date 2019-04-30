#pragma once
#include <winrt/Windows.UI.Xaml.h>
#include <winrt/Windows.ApplicationModel.Activation.h>


namespace Engine {
    struct UwpApplication : winrt::Windows::UI::Xaml::ApplicationT<UwpApplication>
    {
        UwpApplication();
        void OnLaunched(winrt::Windows::ApplicationModel::Activation::LaunchActivatedEventArgs const &);
        
    };
}
