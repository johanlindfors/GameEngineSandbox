#pragma once
#include "IStepTimer.h"

namespace Engine {
    class IGameLoopCallback {
    public:
        virtual void Initialize() = 0;
        virtual void UpdateScreenSize(int width, int height) = 0;
        virtual void Update(std::shared_ptr<Utilities::IStepTimer> timer) = 0;
        virtual void Draw(std::shared_ptr<Utilities::IStepTimer> timer) = 0;
    };
}
