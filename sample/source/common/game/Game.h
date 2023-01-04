#pragma once
#include "game-loop/IGameLoopCallback.h"

namespace Utilities {
    class IStepTimer;
}

namespace Sample {
    class Game : public Engine::IGameLoopCallback
    {
    public:
        Game() = default;
        ~Game();
        // Engine::IGameLoopCallback
        void initialize() override;
        void update(std::shared_ptr<Utilities::IStepTimer> timer) override { }
    };
}
