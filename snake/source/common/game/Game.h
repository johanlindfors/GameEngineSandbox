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

    // IGameLoopCallback
    void Initialize();
    void Update(std::shared_ptr<Utilities::IStepTimer> timer);

    // IGameStateCallback
    void GoToState(GameState gameState);
	GameState GetCurrentState() { return mCurrentState; }

private:
	std::shared_ptr<Engine::ISceneManager> mSceneManager;
	GameState mCurrentState;
    GameState mNextState;
};
