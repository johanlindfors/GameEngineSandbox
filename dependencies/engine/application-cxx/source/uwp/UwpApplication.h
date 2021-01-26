#pragma once

namespace Engine {
    ref class UwpApplication sealed : public Windows::UI::Xaml::Application
    {
	public:
		UwpApplication() { };
        void OnLaunched(Windows::ApplicationModel::Activation::LaunchActivatedEventArgs ^) override;
    };
}
