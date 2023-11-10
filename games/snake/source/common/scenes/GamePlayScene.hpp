#pragma once
// engine
#include "scenes/GameScene.hpp"

// game
#include "game/Systems.hpp"

class IGameStateCallback;

namespace Engine
{
	class IRenderer;
	class IInputManager;
	class IResourceManager;
}

class GamePlayScene : public Engine::GameScene
{
public:
	GamePlayScene(IGameStateCallback *gameCallback);
	~GamePlayScene() = default;

	// Engine::GameScene
	void load() override;
	void unload() override;
	void updateScreenSize(int width, int height) override;
	void update(std::shared_ptr<Utilities::IStepTimer> timer) override;
	void draw(std::shared_ptr<Engine::IRenderer> renderer) override;

private:
	std::shared_ptr<Engine::IInputManager> mInputManager;
	IGameStateCallback *mGame;
	bool mSpacePressedBefore;

	entt::registry mRegistry;
	std::unique_ptr<SpriteSystem> mSpriteSystem;
	std::unique_ptr<MovementSystem> mMovementSystem;
	std::unique_ptr<TransformSystem> mTransformSystem;
	std::unique_ptr<SpawnSystem> mSpawnSystem;
	std::unique_ptr<CleanupSystem> mCleanupSystem;
	std::unique_ptr<ScoringSystem> mScoringSystem;
	std::unique_ptr<CollisionSystem> mCollisionSystem;
	double mElapsedMicroSeconds;
	double mTargetMicroSeconds;
};
