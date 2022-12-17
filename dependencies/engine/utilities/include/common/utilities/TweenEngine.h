#pragma once
#include <memory>
#include <vector>
#include "ITweenEngine.h"
#include "Tween.h"

namespace Utilities
{
    class TweenEngine : public ITweenEngine
    {
        public:
            TweenEngine();
            void Add(int original, std::function<void(int)> setter, int target, int durationInMilliseconds, bool bounce);
            void Update(std::shared_ptr<Utilities::IStepTimer> timer);
        private:
			std::vector<std::shared_ptr<Tween> > mTweens;
    };
}