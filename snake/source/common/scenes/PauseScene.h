#pragma once
#include "scenes/GameScene.h"

namespace Utilities
{
    class IStepTimer;
}

namespace Engine 
{
    struct Sprite;
    class ITextureManager;
    class ISpriteRenderer;
}

class PauseScene : public Engine::GameScene 
{
public:
    PauseScene();
    ~PauseScene() { };

	// Engine::GameScene
    void Load() override;
	void Unload() override { };
	void UpdateScreenSize(int width, int height) override;
	void Update(std::shared_ptr<Utilities::IStepTimer> timer) override { };
	void Draw(std::shared_ptr<Engine::ISpriteRenderer> renderer) override;

private:
	std::shared_ptr<Engine::Sprite> mBackground;
	std::shared_ptr<Engine::Sprite> mText;
    std::shared_ptr<Engine::ITextureManager> mTextureManager;
};