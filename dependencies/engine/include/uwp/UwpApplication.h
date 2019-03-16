#pragma once
#include <winrt/Windows.UI.Xaml.h>
#include <winrt/Windows.ApplicationModel.Activation.h>

class IPlatformProxy;

struct UwpApplication : winrt::Windows::UI::Xaml::ApplicationT<UwpApplication>
{
    UwpApplication(IPlatformProxy* platformProxy = nullptr);
	void OnLaunched(winrt::Windows::ApplicationModel::Activation::LaunchActivatedEventArgs const &);
    
private:
    IPlatformProxy* mPlatformProxy;
};
