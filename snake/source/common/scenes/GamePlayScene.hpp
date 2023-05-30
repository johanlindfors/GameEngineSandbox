#pragma once
#include "scenes/GameScene.hpp"

class IGameStateCallback;
class Apple;
class Snake;
class PointCollider;

namespace Engine 
{
	class IRenderer;
	class IInputManager;
}

class GamePlayScene : public Engine::GameScene 
{
public:
    GamePlayScene(IGameStateCallback* gameCallback);
    ~GamePlayScene() = default;

	// Engine::GameScene
    void load() override;
	void unload() override;
	void updateScreenSize(int width, int height) override;
	void update(std::shared_ptr<Utilities::IStepTimer> timer) override;
	void draw(std::shared_ptr<Engine::IRenderer> renderer) override;

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