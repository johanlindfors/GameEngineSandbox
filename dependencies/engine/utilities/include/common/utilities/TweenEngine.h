#pragma once
#include "ITweenEngine.h"

namespace Utilities
{
    class Tween;

    class TweenEngine : public ITweenEngine
    {
        public:
            TweenEngine();
            void Add(float original, std::function<void(float)> setter, float target, float durationInMilliseconds);
            void Update(std::shared_ptr<Utilities::IStepTimer> timer);
        private:
			std::vector<std::shared_ptr<Tween>> mTweens;
    };
}