#pragma once
#include "scenes/GameScene.h"
#include "textures/ITextureManager.h"
#include "sprites/ISpriteRenderer.h"
#include "IStepTimer.h"
#include <memory>

class PauseScene : public Engine::GameScene 
{
public:
    PauseScene();
    ~PauseScene();
    void Load();
	void Unload();
	void UpdateScreenSize(int width, int height);
	void Update(std::shared_ptr<Utilities::IStepTimer> timer);
	void Draw(std::shared_ptr<Utilities::IStepTimer> timer);

private:
	std::shared_ptr<Engine::Sprite> mBackground;
    std::shared_ptr<Engine::ITextureManager> mTextureManager;
    std::shared_ptr<Engine::ISpriteRenderer> mSpriteRenderer;
};