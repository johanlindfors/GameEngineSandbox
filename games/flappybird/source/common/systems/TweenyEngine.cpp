#include "TweenyEngine.hpp"
#include "utilities/IStepTimer.hpp"

using namespace tweeny;
using tweeny::easing;

void TweenyEngine::add(float original, float target, std::function<void(float)> setter, unsigned int durationInMilliseconds, bool bounce)
{
    tweeny::tween<int> tween;
    if (bounce)
    {
        tween = tweeny::from(static_cast<int>(original)).to(static_cast<int>(target)).during(durationInMilliseconds).via(easing::elasticOut);
    }
    else
    {
        tween = tweeny::from(static_cast<int>(original)).to(static_cast<int>(target)).during(durationInMilliseconds).via(easing::linear);
    }
    tween.onStep([=](tweeny::tween<int> &tween, int value)
                 { 
        setter(value);
        if(tween.progress() >= 1.0f){
            return true;
        }
        return false; });

    mTweenies.push_back(tween);
}

void TweenyEngine::add(float original, float target, std::function<void(float)> setter, unsigned int durationInMilliseconds, bool bounce, std::function<void()> onCompleteCallback)
{
    tweeny::tween<int> tween;
    
    if (bounce)
    {
        tween = tweeny::from(static_cast<int>(original)).to(static_cast<int>(target)).during(durationInMilliseconds).via(easing::elasticOut);
    }
    else
    {
        tween = tweeny::from(static_cast<int>(original)).to(static_cast<int>(target)).during(durationInMilliseconds).via(easing::linear);
    }
    tween.onStep([=](tweeny::tween<int> &tween, int value)
                 { 
        setter(value);
        if(tween.progress() >= 1.0f){
            onCompleteCallback();
            return true;
        }
        return false; });

    mTweenies.push_back(tween);
}

static bool isTweenyCompleted(tweeny::tween<int> tween)
{
    return tween.progress() >= 1;
}

void TweenyEngine::update(std::shared_ptr<Utilities::IStepTimer> timer)
{
    int ms = timer->getElapsedMilliSeconds();
    for (auto &tween : mTweenies)
    {
        tween.step(ms);
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