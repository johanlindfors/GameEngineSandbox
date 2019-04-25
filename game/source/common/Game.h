#pragma once
#include "IGameLoopCallback.h"
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
    void UpdateScreenSize(int width, int height);
    void Update(std::shared_ptr<Utilities::IStepTimer> timer);
    void Draw(std::shared_ptr<Utilities::IStepTimer> timer);

// IGameStateCallback
    void GoToState(GameState gameState);

private:
	std::shared_ptr<Engine::ISceneManager> mSceneManager;
	GameState mCurrentState;
    GameState mNextState;
};
