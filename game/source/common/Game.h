#pragma once
#include "IGameLoopCallback.h"
#include "scenes/SceneManager.h"

class Game : public Engine::IGameLoopCallback
{
public:
    void Initialize();
    void UpdateScreenSize(int width, int height);
    void Update(std::shared_ptr<Utilities::IStepTimer> timer);
    void Draw(std::shared_ptr<Utilities::IStepTimer> timer);

private:
	std::shared_ptr<Engine::ISceneManager> mSceneManager;
};
