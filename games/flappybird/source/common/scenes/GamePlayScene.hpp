#pragma once
#include "scenes/GameScene.hpp"
#include <memory>
#include <vector>
#include <random>
#include "utilities/StepTimer.hpp"

class IGameStateCallback;
class Bird;
class VectorCollider;
class ParallaxBackground;
class Pipes;
class Ground;

namespace Engine
{
	class ITextureManager;
	class IRenderer;
	class IInputManager;
	class IPhysicsEngine;
	struct Sprite;
	class FontRenderer;
}

namespace Engine
{
	class IObjectCollider;
	class ITweenEngine;
}

class GamePlayScene : public Engine::GameScene
{
public:
	GamePlayScene(IGameStateCallback *gameCallback);
	~GamePlayScene();

	// Engine::GameScene
	void load() override;
	void unload() override;
	void updateScreenSize(int width, int height) override;
	void update(std::shared_ptr<Engine::IStepTimer> timer) override;
	void draw(std::shared_ptr<Engine::IRenderer> renderer) override;

private:
	void checkCollisions();
	void generatePipes();
	void reset();

	std::shared_ptr<Engine::Sprite> mInstructions;
	std::unique_ptr<ParallaxBackground> mSkyline;
	std::shared_ptr<Ground> mGround;

	std::shared_ptr<Bird> mBird;
	std::vector<std::shared_ptr<Pipes>> mPipes;
	std::shared_ptr<Engine::IInputManager> mInputManager;
	std::shared_ptr<Engine::IPhysicsEngine> mPhysicsEngine;
	std::shared_ptr<Engine::IObjectCollider> mCollider;
	std::shared_ptr<Engine::ITweenEngine> mTweenEngine;
	int mScreenSizeX;
	int mScreenSizeY;
	IGameStateCallback *mGame;
	bool mSpacePressedBefore;
	bool mShowInstructions;
	Engine::Timer mPipesGenerator;
	std::shared_ptr<Engine::FontRenderer> mFontRenderer;
	int mScore;

	std::mt19937 mGen; // Standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<> mDistrib;
};
