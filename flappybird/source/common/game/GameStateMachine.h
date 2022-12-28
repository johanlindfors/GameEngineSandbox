#pragma once
#include "game-loop/IGameLoopCallback.h"
#include "IGameStateCallback.h"

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
    void Initialize() override;
    void Update(std::shared_ptr<Utilities::IStepTimer> timer) override;

    // Engine::IGameStateCallback
    void GoToState(GameState gameState) override;
	GameState GetCurrentState() override { return mCurrentState; }

private:
    void HandleUnknownState();
    void HandleBootState();
    void HandleSplashState();
    void HandleGamePlayState();
    void HandleGameOverState();
    void HandlePauseState();
    void HandleInstructionsState();

	std::shared_ptr<Engine::ISceneManager> mSceneManager;
	GameState mCurrentState;
    GameState mNextState;
};
