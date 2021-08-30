#pragma once
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.UI.Core.h>
#include <concurrent_queue.h>
#include <functional>
#include "IDispatcherWrapper.h"

namespace Utilities {
    class DispatcherWrapper final : public IDispatcherWrapper {
    public:
        DispatcherWrapper(winrt::Windows::UI::Core::CoreDispatcher const& dispatcher);
        
        winrt::Windows::Foundation::IAsyncAction RunAsync(
            winrt::Windows::UI::Core::DispatchedHandler agileCallback
        ) const;

    	// Utilities::IDispatcherWrapper
        void ScheduleOnGameThread(const std::function<void()>& handler) override;
        void ProcessScheduledFunctions() override;

    private:
        winrt::Windows::UI::Core::CoreDispatcher mDispatcher = { nullptr };
        concurrency::concurrent_queue<std::function<void()>> mScheduledFunctions;
    };
}
