#pragma once
#include "game-loop/IGameLoopCallback.hpp"
#include "IGameStateCallback.hpp"

namespace Engine
{
    class ISceneManager;
}

namespace Utilities
{
    class IStepTimer;
}

class Game : public Engine::IGameLoopCallback, public IGameStateCallback
{
public:
    Game();

    // Engine::IGameLoopCallback
    void initialize() override;
    void update(std::shared_ptr<Utilities::IStepTimer> timer) override;

    // Engine::IGameStateCallback
    void goToState(GameState gameState) override;
    GameState getCurrentState() override { return mCurrentState; }

private:
    void handleUnknownState();
    void handleBootState();
    void handleSplashState();
    void handleGamePlayState();
    void handleGameOverState();
    void handlePauseState();

    std::shared_ptr<Engine::ISceneManager> mSceneManager;
    GameState mCurrentState;
    GameState mNextState;
};
