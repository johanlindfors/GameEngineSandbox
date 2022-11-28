#pragma once
#include "scenes/GameScene.h"
#include <memory>
#include <queue>
#include "objects/Clouds.h"

class IGameStateCallback;

namespace Engine
{
	class ITextureManager;
	class ISpriteRenderer;
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
	void Draw(std::shared_ptr<Utilities::IStepTimer> timer) override;

private:
	std::shared_ptr<Engine::Sprite> mBackground;
	std::shared_ptr<Engine::Sprite> mTitle;
	std::unique_ptr<Clouds> mClouds;
	std::shared_ptr<Engine::Sprite> mGround;
	std::shared_ptr<Engine::Sprite> mTrees;
	std::shared_ptr<Engine::Sprite> mCity;
	float mMillisecondsToLoad;
	bool mHasLoadedGamePlay;
	bool mIsLoadingResources;
	int mWindowWidth;
	int mWindowHeight;

	std::shared_ptr<Engine::ITextureManager> mTextureManager;
    std::shared_ptr<Engine::ISpriteRenderer> mSpriteRenderer;
	IGameStateCallback* mGame;
};