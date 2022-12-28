#pragma once
#include "scenes/GameScene.h"

class IGameStateCallback;
class Apple;
class Snake;
class PointCollider;

namespace Engine 
{
	class ISpriteRenderer;
	class IInputManager;
}

class GamePlayScene : public Engine::GameScene 
{
public:
    GamePlayScene(IGameStateCallback* gameCallback);
    ~GamePlayScene() = default;

	// Engine::GameScene
    void Load() override;
	void Unload() override;
	void UpdateScreenSize(int width, int height) override;
	void Update(std::shared_ptr<Utilities::IStepTimer> timer) override;
	void Draw(std::shared_ptr<Engine::ISpriteRenderer> renderer) override;

private:
	std::shared_ptr<Apple> mApple;
	std::shared_ptr<Snake> mSnake;
	std::shared_ptr<PointCollider> mCollider;

	std::shared_ptr<Engine::IInputManager> mInputManager;
	int mScreenSizeX;
	int mScreenSizeY;
	IGameStateCallback* mGame;
	bool mSpacePressedBefore;
};