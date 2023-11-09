#pragma once
#include <memory>
#include <vector>
#include "ITweenEngine.hpp"
#include "Tween.hpp"

namespace Utilities
{
    class TweenEngine : public ITweenEngine
    {
    public:
        TweenEngine();
        void add(float original, float target, std::function<void(float)> setter, unsigned int durationInMilliseconds, bool bounce);
        void add(float original, float target, std::function<void(float)> setter, unsigned int durationInMilliseconds, bool bounce, std::function<void()> onCompleteCallback);
        void update(std::shared_ptr<Utilities::IStepTimer> timer);
        void clear();

    private:
        std::vector<std::shared_ptr<Tween>> mTweens;
    };
}