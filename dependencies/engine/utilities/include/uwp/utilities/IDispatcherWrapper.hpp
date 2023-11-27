#pragma once
#include <functional>

namespace Utilities
{
    class IDispatcherWrapper
    {
    public:
        virtual ~IDispatcherWrapper() = default;
        virtual void ScheduleOnGameThread(const std::function<void()> &handler) = 0;
        virtual void ProcessScheduledFunctions() = 0;
    };
}
