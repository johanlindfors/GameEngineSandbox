#pragma once
#include <memory>
#include "utilities/IStepTimer.hpp"

namespace Engine
{
    class IGameLoopCallback
    {
    public:
        virtual ~IGameLoopCallback() = default;
        virtual void initialize() = 0;
        virtual void update(std::shared_ptr<Utilities::IStepTimer> timer) = 0;
    };
}
