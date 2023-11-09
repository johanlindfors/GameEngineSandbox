#include "DispatcherWrapper.hpp"
#include <concurrent_queue.h>

using namespace std;
using namespace winrt;
using namespace Windows::UI::Core;
using namespace Windows::Foundation;
using namespace Utilities;

DispatcherWrapper::DispatcherWrapper(CoreDispatcher const &dispatcher)
    : mDispatcher(dispatcher) {}

IAsyncAction DispatcherWrapper::RunAsync(DispatchedHandler agileCallback) const
{
    return mDispatcher.RunAsync(CoreDispatcherPriority::Normal, agileCallback);
}

void DispatcherWrapper::ScheduleOnGameThread(const function<void()> &handler)
{
    mScheduledFunctions.push(handler);
}

void DispatcherWrapper::ProcessScheduledFunctions()
{
    function<void()> function;
    while (mScheduledFunctions.try_pop(function))
    {
        function();
    }
}
