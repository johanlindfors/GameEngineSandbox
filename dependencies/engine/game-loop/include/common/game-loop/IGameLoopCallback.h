#pragma once
#include <memory>
#include "IStepTimer.h"

namespace Engine {
    class IGameLoopCallback {
    public:
	    virtual ~IGameLoopCallback() = default;
	    virtual void Initialize() = 0;
        virtual void Update(std::shared_ptr<Utilities::IStepTimer> timer) = 0;
    };
}
