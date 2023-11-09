#include "utilities/TweenEngine.hpp"
#include "utilities/Tween.hpp"

using namespace std;
using namespace Utilities;

TweenEngine::TweenEngine()
    : mTweens(vector<shared_ptr<Tween>>())
{
}

void TweenEngine::add(float original, float target, function<void(float)> setter, unsigned int durationInMilliseconds, bool bounce)
{
    mTweens.push_back(make_unique<Tween>(original, target, setter, durationInMilliseconds, nullptr));
}

void TweenEngine::add(float original, float target, function<void(float)> setter, unsigned int durationInMilliseconds, bool bounce, function<void()> onCompleteCallback)
{
    mTweens.push_back(make_unique<Tween>(original, target, setter, durationInMilliseconds, onCompleteCallback));
}

void TweenEngine::update(shared_ptr<IStepTimer> timer)
{
    for (auto tween : mTweens)
    {
        tween->update(timer);
    }
    mTweens.erase(remove_if(mTweens.begin(), mTweens.end(), Tween::isTweenCompleted),
                  mTweens.end());
}

void TweenEngine::clear()
{
    mTweens.clear();
}