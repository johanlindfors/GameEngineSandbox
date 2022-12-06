#include "TweenyEngine.h"
#include "utilities/IStepTimer.h"

using namespace tweeny;
using tweeny::easing;

void TweenyEngine::Add(int original, std::function<void(int)> setter, int target, int durationInMilliseconds, bool bounce)
{
    tweeny::tween<int> tween;
    if(bounce) {
        tween = tweeny::from(original).
                        to(target).
                        during(durationInMilliseconds).
                        via(easing::elasticOut);
    } else {
        tween = tweeny::from(original).
                        to(target).
                        during(durationInMilliseconds).
                        via(easing::linear);
    }
    tween.onStep([=](tweeny::tween<int> & tween, int value){ 
        setter(value);
        if(tween.progress() >= 1.0f)
                return true;
        return false;
    });

    mTweenies.push_back(tween);
}

static bool IsTweenyCompleted(tweeny::tween<int> tween) {
    if(tween.progress() >= 1)
        return true;
    return false;
}

void TweenyEngine::Update(std::shared_ptr<Utilities::IStepTimer> timer)
{
    for(auto &tween : mTweenies) {
        auto ms = timer->GetElapsedMilliSeconds();
        tween.step(timer->GetElapsedMilliSeconds());
    }

    mTweenies.erase(
        remove_if(
            mTweenies.begin(), 
            mTweenies.end(), 
            IsTweenyCompleted),
        mTweenies.end());
}