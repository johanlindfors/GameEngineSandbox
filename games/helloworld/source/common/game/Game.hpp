#pragma once
#include "game-loop/IGameLoopCallback.hpp"

class Game : public Engine::IGameLoopCallback
{
public:
    inline Game() { }
    virtual ~Game() { }

    // Engine::IGameLoopCallback
    void initialize() override;
    void update(std::shared_ptr<Utilities::IStepTimer> timer) override { }
};
