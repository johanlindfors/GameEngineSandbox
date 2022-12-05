#pragma once
#include <functional>
#include <memory>

namespace Utilities
{
    class IStepTimer;
    
    class ITweenEngine
    {
        public:
            virtual void Add(float original, std::function<void(float)> setter, float target, float durationInMilliseconds) = 0;
            virtual void Update(std::shared_ptr<Utilities::IStepTimer> timer) = 0;
    };
}