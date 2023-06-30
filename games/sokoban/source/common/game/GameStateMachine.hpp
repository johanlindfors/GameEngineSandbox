#pragma once

// stl
#include <memory>

// engine
#include "game-loop/IGameLoopCallback.hpp"

// game
#include "IGameStateCallback.hpp"

namespace Engine {
    class ISceneManager;
}

namespace Utilities {
    class IStepTimer;
}

class GameStateMachine : public Engine::IGameLoopCallback, public IGameStateCallback
{
public:
    GameStateMachine();

    // Engine::IGameLoopCallback
    void initialize() override;
    void update(std::shared_ptr<Utilities::IStepTimer> timer) override;

    // Engine::IGameStateCallback
    void goToState(GameState gameState) override;
	GameState getCurrentState() override { return mCurrentState; }

private:
    void handleUnknownState();
    void handleBootState();
    void handleGamePlayState();
    void handleGameOverState();

	std::shared_ptr<Engine::ISceneManager> mSceneManager;
	GameState mCurrentState;
    GameState mNextState;
};
