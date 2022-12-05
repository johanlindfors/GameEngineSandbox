#pragma once
#include "scenes/GameScene.h"
#include <memory>
#include <vector>
#include "StepTimer.h"

class IGameStateCallback;
class Bird;
class VectorCollider;
class ParallaxBackground;
class Pipes;

namespace Engine 
{
	class ITextureManager;
	class ISpriteRenderer;
	class IInputManager;
	class IPhysicsEngine;
	class Sprite;
}

namespace Utilities
{
	class IObjectCollider;
	class ITweenEngine;
}

class GamePlayScene : public Engine::GameScene 
{
public:
    GamePlayScene(IGameStateCallback* gameCallback);
    ~GamePlayScene();

	// Engine::GameScene
    void Load() override;
	void Unload() override;
	void UpdateScreenSize(int width, int height) override;
	void Update(std::shared_ptr<Utilities::IStepTimer> timer) override;
	void Draw(std::shared_ptr<Engine::ISpriteRenderer> renderer) override;

private:
	void GeneratePipes();

	std::shared_ptr<Engine::Sprite> mBackground;
	std::unique_ptr<ParallaxBackground> mSkyline;
	std::shared_ptr<Bird> mBird;
	std::vector<std::shared_ptr<Pipes>> mPipes;
	std::shared_ptr<Engine::ITextureManager> mTextureManager;
	std::shared_ptr<Engine::IInputManager> mInputManager;
	std::shared_ptr<Engine::IPhysicsEngine> mPhysicsEngine;
	std::shared_ptr<Utilities::IObjectCollider> mCollider;
	std::shared_ptr<Utilities::ITweenEngine> mTweenEngine;
	int mScreenSizeX;
	int mScreenSizeY;
	IGameStateCallback* mGame;
	bool mSpacePressedBefore;
	Utilities::Timer mPipesGenerator;
}; 