#pragma once
#include <memory>
#include <vector>
#include <functional>
#include "ITweenEngine.hpp"
#include "Tween.hpp"

namespace Engine
{
    class TweenEngine : public ITweenEngine
    {
    public:
        TweenEngine();
        void add(float original, float target, std::function<void(float)> setter, unsigned int durationInMilliseconds, bool bounce);
        void add(float original, float target, std::function<void(float)> setter, unsigned int durationInMilliseconds, bool bounce, std::function<void()> onCompleteCallback);
        void update(std::shared_ptr<Engine::IStepTimer> timer);
        void clear();

    private:
        std::vector<std::shared_ptr<Tween>> mTweens;
    };
}