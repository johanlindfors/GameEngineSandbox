#pragma once
#include "game-loop/IGameLoopCallback.hpp"

namespace Engine
{
    class IStepTimer;
}

namespace Sample
{
    class Game : public Engine::IGameLoopCallback
    {
    public:
        Game() = default;
        ~Game() = default;

        // Engine::IGameLoopCallback
        void initialize() override;
        void update(std::shared_ptr<Engine::IStepTimer> timer) override {}
    };
}
