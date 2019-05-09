#pragma once
#include "IStepTimer.h"
#include <memory>

namespace Engine {
    class IGameLoopCallback {
    public:
        virtual void Initialize() = 0;
        virtual void Update(std::shared_ptr<Utilities::IStepTimer> timer) = 0;
    };
}
