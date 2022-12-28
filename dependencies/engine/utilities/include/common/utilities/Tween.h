#pragma once
#include <functional>
#include <memory>

namespace Utilities
{
    class IStepTimer;

	class Tween
    {
		public:
			bool IsComplete;

			Tween(float original, std::function<void(float)> setter, float target, float durationInMilliseconds);
			void Update(std::shared_ptr<Utilities::IStepTimer> timer);

			static bool IsTweenCompleted(std::shared_ptr<Tween> tween)
			{
                if(tween->IsComplete) {
                    tween.reset();
                    return true;
                }
                return false;
			}
			
		private:
			float duration;
			float elapsed;
			float targetValue;
			float originalValue;
			std::function<void(float)> tweenFunc;
    };
}