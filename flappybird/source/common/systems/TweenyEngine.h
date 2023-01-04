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
        void add(int original, std::function<void(int)> setter, int target, int durationInMilliseconds, bool bounce);
        void update(std::shared_ptr<Utilities::IStepTimer> timer);
        void clear();
    private:
        std::vector<tweeny::tween<int>> mTweenies;
};