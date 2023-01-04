#pragma once
#include "scenes/GameScene.h"

namespace Utilities
{
    class IStepTimer;
}

namespace Engine 
{
    struct Sprite;
    class IResourceManager;
    class IRenderer;
}

class PauseScene : public Engine::GameScene 
{
public:
    PauseScene();
    ~PauseScene() { };

	// Engine::GameScene
    void load() override;
	void unload() override { };
	void updateScreenSize(int width, int height) override;
	void update(std::shared_ptr<Utilities::IStepTimer> timer) override { };
	void draw(std::shared_ptr<Engine::IRenderer> renderer) override;

private:
	std::shared_ptr<Engine::Sprite> mBackground;
	std::shared_ptr<Engine::Sprite> mText;
};