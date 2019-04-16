#pragma once
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.UI.Core.h>
#include <concurrent_queue.h>

class DispatcherWrapper {
public:
    DispatcherWrapper(winrt::Windows::UI::Core::CoreDispatcher const& dispatcher)
        : mDispatcher(dispatcher)
    {}

    winrt::Windows::Foundation::IAsyncAction RunAsync(
        winrt::Windows::UI::Core::DispatchedHandler agileCallback
    ) const
    {
        return mDispatcher.RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::Normal, agileCallback);
    }

	void ScheduleOnGameThread(const std::function<void()>& handler) {
		mScheduledFunctions.push(handler);
	}

	void ProcessScheduledFunctions() {
		std::function<void()> function;
		while (mScheduledFunctions.try_pop(function)) {
			function();
		}
	}

private:
    winrt::Windows::UI::Core::CoreDispatcher mDispatcher = { nullptr };
	concurrency::concurrent_queue<std::function<void()>> mScheduledFunctions;
};