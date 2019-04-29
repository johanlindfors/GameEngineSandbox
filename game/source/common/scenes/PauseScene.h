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
    void Load();
	void Unload() { };
	void UpdateScreenSize(int width, int height);
	void Update(std::shared_ptr<Utilities::IStepTimer> timer) { };
	void Draw(std::shared_ptr<Utilities::IStepTimer> timer);

private:
	std::shared_ptr<Engine::Sprite> mBackground;
	std::shared_ptr<Engine::Sprite> mText;
    std::shared_ptr<Engine::ITextureManager> mTextureManager;
    std::shared_ptr<Engine::ISpriteRenderer> mSpriteRenderer;
};