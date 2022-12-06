#pragma once
#include "utilities/ITweenEngine.h"
#include "utilities/IStepTimer.h"
#include <vector>
#include <memory>
#include "tweeny.h"

class TweenyEngine : public Utilities::ITweenEngine
{
    public:
        TweenyEngine() { }
        void Add(int original, std::function<void(int)> setter, int target, int durationInMilliseconds, bool bounce);
        void Update(std::shared_ptr<Utilities::IStepTimer> timer);
    private:
        std::vector<tweeny::tween<int>> mTweenies;
};