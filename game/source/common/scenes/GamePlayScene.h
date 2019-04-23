#pragma once
#include "scenes/GameScene.h"
#include "textures/ITextureManager.h"
#include "sprites/ISpriteRenderer.h"
#include "input/IInputManager.h"
#include "MathHelper.h"
#include "game-objects/Snake.h"
#include "game-objects/Apple.h"
#include <ctime>
#include <list>

class GamePlayScene : public Engine::GameScene 
{
public:
    GamePlayScene();
    ~GamePlayScene();
    void Load();
	void Unload();
	void UpdateScreenSize(int width, int height);
	void Update(std::shared_ptr<Utilities::IStepTimer> timer);
	void Draw(std::shared_ptr<Utilities::IStepTimer> timer);

private:
	void HandleInput();

	std::shared_ptr<Apple> mApple;
	std::shared_ptr<Snake> mSnake;

	std::shared_ptr<Engine::ITextureManager> mTextureManager;
    std::shared_ptr<Engine::ISpriteRenderer> mSpriteRenderer;
	std::shared_ptr<Engine::IInputManager> mInputManager;
	int mScreenSizeX;
	int mScreenSizeY;
};