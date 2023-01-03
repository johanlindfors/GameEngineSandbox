#pragma once
#include "game-loop/IGameLoopCallback.h"

namespace Utilities {
    class IStepTimer;
}

class GameStateMachine : public Engine::IGameLoopCallback
{
public:
    GameStateMachine() = default;

    // Engine::IGameLoopCallback
    void Initialize() override;
    void Update(std::shared_ptr<Utilities::IStepTimer> timer) override { }
};
