#pragma once
#include <functional>
#include <memory>

namespace Utilities
{
	class IStepTimer;

	class Tween
	{
	public:
		bool isComplete;

		Tween(
			float original,
			float target,
			std::function<void(float)> setter,
			unsigned int durationInMilliseconds,
			std::function<void()> onCompleteCallback);
		void update(std::shared_ptr<Utilities::IStepTimer> timer);

		static bool isTweenCompleted(std::shared_ptr<Tween> tween)
		{
			if (tween->isComplete)
			{
				tween.reset();
				return true;
			}
			return false;
		}

	private:
		unsigned int duration;
		unsigned int elapsed;
		float targetValue;
		float originalValue;
		std::function<void(float)> tweenFunc;
		std::function<void()> onCompleteCallback;
	};
}
