#pragma once
#include "scenes/GameScene.h"
#include <memory>
#include <vector>

class IGameStateCallback;
class Bird;
class VectorCollider;
class ParallaxBackground;

namespace Engine 
{
	class ITextureManager;
	class ISpriteRenderer;
	class IInputManager;
	class Sprite;
}

class IPhysicsBody;

class PhysicsEngine 
{
private:
	const float GRAVITY = 9.1f;
    std::vector<std::shared_ptr<IPhysicsBody>> mBodies;

public:
	void AddBody(std::shared_ptr<IPhysicsBody> body);
	void Update(std::shared_ptr<Utilities::IStepTimer> timer);
};

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
	std::shared_ptr<Engine::Sprite> mBackground;
	std::unique_ptr<ParallaxBackground> mSkyline;
	std::shared_ptr<Bird> mBird;
	std::shared_ptr<VectorCollider> mCollider;
	std::shared_ptr<Engine::ITextureManager> mTextureManager;
	std::shared_ptr<Engine::IInputManager> mInputManager;
	std::unique_ptr<PhysicsEngine> mPhysicsEngine;
	int mScreenSizeX;
	int mScreenSizeY;
	IGameStateCallback* mGame;
	bool mSpacePressedBefore;
}; 