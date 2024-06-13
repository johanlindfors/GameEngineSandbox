#pragma once
#include "scenes/GameScene.hpp"
#include "game/IGameStateCallback.hpp"
#include <memory>

class IGameStateCallback;

namespace Engine
{
	class IRenderer;
}

namespace Utilities
{
	class IStepTimer;
}

class BootScene : public Engine::GameScene
{
public:
	BootScene(IGameStateCallback *gameCallback);
	~BootScene();

	// Engine::GameScene
	void load() override;
	void unload() override;
	void updateScreenSize(int width, int height) override;
	void update(std::shared_ptr<Utilities::IStepTimer> timer) override;
	void draw(std::shared_ptr<Engine::IRenderer> renderer) override;

    private:
        bool mResourcesLoaded = false;
        IGameStateCallback *mGame;
};