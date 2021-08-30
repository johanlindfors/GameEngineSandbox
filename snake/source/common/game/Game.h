#pragma once
#include "game-loop/IGameLoopCallback.h"
#include "IGameStateCallback.h"

namespace Engine {
    class ISceneManager;
}

namespace Utilities {
    class IStepTimer;
}

class Game : public Engine::IGameLoopCallback, public IGameStateCallback
{
public:
    Game();

    // Engine::IGameLoopCallback
    void Initialize() override;
    void Update(std::shared_ptr<Utilities::IStepTimer> timer) override;

    // Engine::IGameStateCallback
    void GoToState(GameState gameState) override;
	GameState GetCurrentState() override { return mCurrentState; }

private:
	std::shared_ptr<Engine::ISceneManager> mSceneManager;
	GameState mCurrentState;
    GameState mNextState;
};
