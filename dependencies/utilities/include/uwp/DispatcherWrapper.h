#pragma once
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.UI.Core.h>

class DispatcherWrapper {
public:
    DispatcherWrapper(winrt::Windows::UI::Core::CoreDispatcher const& dispatcher)
        : mDispatcher(dispatcher)
    {}

    winrt::Windows::Foundation::IAsyncAction DispatcherWrapper::RunAsync(
        winrt::Windows::UI::Core::DispatchedHandler agileCallback
    ) const
    {
        return mDispatcher.RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::Normal, agileCallback);
    }
private:
    winrt::Windows::UI::Core::CoreDispatcher mDispatcher = { nullptr };
};