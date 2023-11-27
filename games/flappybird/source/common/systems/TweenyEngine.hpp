#pragma once
#include "utilities/ITweenEngine.hpp"
#include "utilities/IStepTimer.hpp"
#include <vector>
#include <memory>
#include "tweeny.h"
#include <functional>

class TweenyEngine : public Utilities::ITweenEngine
{
public:
    TweenyEngine() {}
    void add(float original, float target, std::function<void(float)> setter, unsigned int durationInMilliseconds, bool bounce);
    void add(float original, float target, std::function<void(float)> setter, unsigned int durationInMilliseconds, bool bounce, std::function<void()> onCompleteCallback);
    void update(std::shared_ptr<Utilities::IStepTimer> timer);
    void clear();

private:
    std::vector<tweeny::tween<int>> mTweenies;
};