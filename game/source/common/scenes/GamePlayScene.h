#pragma once
#include "scenes/GameScene.h"
#include "textures/ITextureManager.h"
#include "sprites/ISpriteRenderer.h"
#include "input/IInputManager.h"

class GamePlayScene : public GameScene 
{
public:
    GamePlayScene();
    ~GamePlayScene();
    void Load();
	void Unload();
	void UpdateScreenSize(int width, int height);
	void Update(Utilities::StepTimer const& timer);
	void Draw(Utilities::StepTimer const& timer);

private:
	Sprite mApple;

	std::shared_ptr<ITextureManager> mTextureManager;
    std::shared_ptr<ISpriteRenderer> mSpriteRenderer;
	std::shared_ptr<IInputManager> mInputManager;
	int mScreenSizeX;
	int mScreenSizeY;
};