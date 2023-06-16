#include "utilities/Tween.hpp"
#include "utilities/IStepTimer.hpp"
#include "utilities/MathHelper.hpp"

using namespace std;
using namespace Utilities;

Tween::Tween(float original, function<void(float)> setter, float target, float durationInMilliseconds, function<void()> onCompleteCallback = nullptr)
    : originalValue(original)
    , targetValue(target)
    , tweenFunc(setter)
    , duration(durationInMilliseconds)
    , elapsed(0)
    , isComplete(false)
    , onCompleteCallback(onCompleteCallback)
{ }

void Tween::update(shared_ptr<IStepTimer> timer)
{
    elapsed += timer->getElapsedMilliSeconds();
    float currentValue = targetValue;
    if(elapsed <= duration) {
        currentValue = Utilities::lerp(originalValue, targetValue, elapsed / duration);
    } else {
        isComplete = true;
        if(onCompleteCallback) {
            onCompleteCallback();
        }
    }
    tweenFunc(currentValue);
}
