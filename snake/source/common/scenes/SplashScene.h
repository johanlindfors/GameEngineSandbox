#pragma once
#include "scenes/GameScene.h"
#include <memory>
#include <queue>

class IGameStateCallback;

namespace Engine
{
	class IRenderer;
	class IResourceManager;
	struct Sprite;
}

namespace Utilities
{
	class IStepTimer;
}

class SplashScene : public Engine::GameScene 
{
public:
    SplashScene(IGameStateCallback* gameCallback);
    ~SplashScene();

	// Engine::GameScene
    void load() override;
	void unload() override;
	void updateScreenSize(int width, int height) override;
	void update(std::shared_ptr<Utilities::IStepTimer> timer) override;
	void draw(std::shared_ptr<Engine::IRenderer> renderer) override;

private:
	std::shared_ptr<Engine::Sprite> mSprite;
	float mMillisecondsToLoad;
	bool hasLoadedGamePlay;
	bool isLoadingResources;
	std::queue<std::string> mResourcesToLoad;
	std::shared_ptr<Engine::IResourceManager> mResourceManager;

	IGameStateCallback* mGame;
};