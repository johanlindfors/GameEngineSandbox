#pragma once
#include "scenes/GameScene.h"
#include <memory>
#include <queue>

class IGameStateCallback;
class ParallaxBackground;
class Bird;
class Ground;

namespace Engine
{
	class IResourceManager;
	class IInputManager;
	class IRenderer;
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
    void Load() override;
	void Unload() override;
	void UpdateScreenSize(int width, int height) override;
	void Update(std::shared_ptr<Utilities::IStepTimer> timer) override;
	void Draw(std::shared_ptr<Engine::IRenderer> renderer) override;

private:
	std::shared_ptr<Engine::Sprite> mBackground;
	std::shared_ptr<ParallaxBackground> mSkyline;
	std::shared_ptr<Ground> mGround;
	std::shared_ptr<Engine::Sprite> mTitle;
	std::shared_ptr<Engine::Sprite> mButton;
	std::shared_ptr<Bird> mBird;
	float mMillisecondsToLoad;
	bool mHasLoadedGamePlay;
	bool mIsLoadingResources;
	int mWindowWidth;
	int mWindowHeight;
	bool mSpacePressedBefore;

	std::shared_ptr<Engine::IResourceManager> mResourceManager;
	std::shared_ptr<Engine::IInputManager> mInputManager;
	IGameStateCallback* mGame;
};