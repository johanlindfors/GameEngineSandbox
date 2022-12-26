#pragma once
#include <functional>
#include <memory>

namespace Utilities
{
    class IStepTimer;
    
    class ITweenEngine
    {
        public:
            virtual void Add(int original, std::function<void(int)> setter, int target, int durationInMilliseconds, bool bounce) = 0;
            virtual void Update(std::shared_ptr<Utilities::IStepTimer> timer) = 0;
            virtual void Clear() = 0;
    };
}