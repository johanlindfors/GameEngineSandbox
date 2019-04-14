#pragma once
#include "scenes/GameScene.h"
#include "textures/ITextureManager.h"
#include "sprites/ISpriteRenderer.h"

class SplashScene : public GameScene 
{
public:
    SplashScene();
    ~SplashScene();
    void Load();
	void Unload();
	void UpdateScreenSize(int width, int height);
	void Update(Utilities::StepTimer const& timer);
	void Draw(Utilities::StepTimer const& timer);

private:
	Sprite mSprite;

	std::shared_ptr<ITextureManager> mTextureManager;
    std::shared_ptr<ISpriteRenderer> mSpriteRenderer;
};