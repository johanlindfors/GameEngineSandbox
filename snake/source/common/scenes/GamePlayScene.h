#pragma once
#include "scenes/GameScene.h"

class IGameStateCallback;
class Apple;
class Snake;
class VectorCollider;

namespace Engine 
{
	class ITextureManager;
	class ISpriteRenderer;
	class IInputManager;
}

class GamePlayScene : public Engine::GameScene 
{
public:
    GamePlayScene(IGameStateCallback* gameCallback);
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
	std::shared_ptr<VectorCollider> mCollider;

	std::shared_ptr<Engine::ITextureManager> mTextureManager;
    std::shared_ptr<Engine::ISpriteRenderer> mSpriteRenderer;
	std::shared_ptr<Engine::IInputManager> mInputManager;
	int mScreenSizeX;
	int mScreenSizeY;
	IGameStateCallback* mGame;
	bool mSpacePressedBefore;
};