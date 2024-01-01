#pragma once
#include <functional>
#include <memory>

namespace Engine
{
    class IStepTimer;

    class ITweenEngine
    {
    public:
        virtual void add(float original, float target, std::function<void(float)> setter, unsigned int durationInMilliseconds, bool bounce) = 0;
        virtual void add(float original, float target, std::function<void(float)> setter, unsigned int durationInMilliseconds, bool bounce, std::function<void()> onCompleteCallback) = 0;
        virtual void update(std::shared_ptr<Engine::IStepTimer> timer) = 0;
        virtual void clear() = 0;
    };
}