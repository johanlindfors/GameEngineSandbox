#include "TweenyEngine.hpp"
#include "utilities/IStepTimer.hpp"

using namespace tweeny;
using namespace tweeny::easing;

void TweenyEngine::add(float original, float target, std::function<void(float)> setter, unsigned int durationInMilliseconds, bool bounce)
{
    auto tween = tweeny::from(static_cast<int>(original))
        .to(static_cast<int>(target))
        .during(durationInMilliseconds)
        .via(tweeny::easing::byName(bounce ? "elasticOut" : "linear"))
        .build();
    tween.on(tweeny::event::step, [=](auto &tween){ 
        auto value = tween.peek();
        setter(value);
        if(tween.progress() >= 1.0f){
            return tweeny::event::response::unsubscribe;
        }
        return tweeny::event::response::ok; }
    );

    mTweenies.push_back(tween);
}

void TweenyEngine::add(float original, float target, std::function<void(float)> setter, unsigned int durationInMilliseconds, bool bounce, std::function<void()> onCompleteCallback)
{
    auto tween = tweeny::from(static_cast<int>(original))
        .to(static_cast<int>(target))
        .during(durationInMilliseconds)
        .via(tweeny::easing::byName(bounce ? "elasticOut" : "linear"))
        .build();
    
    tween.on(tweeny::event::step, [=](auto &tween){ 
        auto value = tween.peek();
        setter(value);
        if(tween.progress() >= 1.0f){
            onCompleteCallback();
            return tweeny::event::response::unsubscribe;
        }
        return tweeny::event::response::ok; });

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