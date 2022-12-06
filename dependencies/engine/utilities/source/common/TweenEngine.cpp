#include "utilities/TweenEngine.h"
#include "utilities/Tween.h"

using namespace std;
using namespace Utilities;

TweenEngine::TweenEngine()
    : mTweens(vector<shared_ptr<Tween>>())
{ }

void TweenEngine::Add(int original, function<void(int)> setter, int target, int durationInMilliseconds, bool bounce)
{
    mTweens.push_back(make_unique<Tween>(original, setter, target, durationInMilliseconds));
}

void TweenEngine::Update(shared_ptr<IStepTimer> timer)
{
    for(auto tween : mTweens) {
        tween->Update(timer);
    }
    mTweens.erase(remove_if(mTweens.begin(), mTweens.end(), Tween::IsTweenCompleted),
        mTweens.end());
}