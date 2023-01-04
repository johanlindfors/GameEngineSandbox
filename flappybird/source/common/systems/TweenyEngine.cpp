#include "TweenyEngine.h"
#include "utilities/IStepTimer.h"

using namespace tweeny;
using tweeny::easing;

void TweenyEngine::add(int original, std::function<void(int)> setter, int target, int durationInMilliseconds, bool bounce)
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

static bool isTweenyCompleted(tweeny::tween<int> tween) {
    if(tween.progress() >= 1)
        return true;
    return false;
}

void TweenyEngine::update(std::shared_ptr<Utilities::IStepTimer> timer)
{
    for(auto &tween : mTweenies) {
        auto ms = timer->getElapsedMilliSeconds();
        tween.step(timer->getElapsedMilliSeconds());
    }

    mTweenies.erase(
        remove_if(
            mTweenies.begin(), 
            mTweenies.end(), 
            isTweenyCompleted),
        mTweenies.end());
}

void TweenyEngine::clear() 
{
    mTweenies.clear();
}