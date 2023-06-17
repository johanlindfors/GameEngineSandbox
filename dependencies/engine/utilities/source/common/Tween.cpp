#include "utilities/Tween.hpp"
#include "utilities/IStepTimer.hpp"
#include "utilities/MathHelper.hpp"

using namespace std;
using namespace Utilities;

Tween::Tween(
    float original, 
    float target, 
    function<void(float)> setter, 
    unsigned int durationInMilliseconds, 
    function<void()> onCompleteCallback = nullptr
)
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
    auto delta = timer->getDeltaMicroSeconds();
    elapsed += delta;
    float currentValue = targetValue;
    if(elapsed <= duration) {
        currentValue = Utilities::lerp(originalValue, targetValue, static_cast<float>(elapsed) / static_cast<float>(duration));
    } else {
        isComplete = true;
        if(onCompleteCallback) {
            onCompleteCallback();
        }
    }
    tweenFunc(currentValue);
}
