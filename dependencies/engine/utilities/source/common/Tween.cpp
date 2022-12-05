#include "Tween.h"
#include "IStepTimer.h"
#include "MathHelper.h"

using namespace std;
using namespace Utilities;

Tween::Tween(float original, function<void(float)> setter, float target, float durationInMilliseconds)
    : originalValue(original)
    , targetValue(target)
    , tweenFunc(setter)
    , duration(durationInMilliseconds)
    , elapsed(0)
    , IsComplete(false)
{ }

void Tween::Update(shared_ptr<IStepTimer> timer)
{
    elapsed += timer->GetElapsedMilliSeconds();
    float currentValue = targetValue;
    if(elapsed <= duration) {
        currentValue = Utilities::Lerp(originalValue, targetValue, elapsed / duration);
    } else {
        IsComplete = true;
    }
    tweenFunc(currentValue);
}
