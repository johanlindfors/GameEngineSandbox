#pragma once
#include "scenes/GameScene.hpp"
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
    GamePlayScene(IGameStateCallback* gameCallback);
    ~GamePlayScene() = default;

	// Engine::GameScene
    void load() override;
	void unload() override;
	void updateScreenSize(int width, int height) override;
	void update(std::shared_ptr<Utilities::IStepTimer> timer) override;
	void draw(std::shared_ptr<Engine::IRenderer> renderer) override;

private:
	void spawnApple();

	std::shared_ptr<Engine::IInputManager> mInputManager;
	std::shared_ptr<Engine::IResourceManager> mResourceManager;
	int mScreenSizeX;
	int mScreenSizeY;
	IGameStateCallback* mGame;
	bool mSpacePressedBefore;

	entt::registry mRegistry;
	std::unique_ptr<sprite_system> mSpriteSystem;
	std::unique_ptr<movement_system> mMovementSystem;
	std::unique_ptr<transform_system> mTransformSystem;
	std::unique_ptr<spawn_system> mSpawnSystem;
	std::unique_ptr<cleanup_system> mCleanupSystem;
	std::unique_ptr<scoring_system> mScoringSystem;
	std::unique_ptr<collision_system> mCollisionSystem;
};
