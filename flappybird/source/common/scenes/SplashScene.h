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
	class ITextureManager;
	class IInputManager;
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
	void Draw(std::shared_ptr<Engine::ISpriteRenderer> renderer) override;

private:
	std::shared_ptr<Engine::Sprite> mBackground;
	std::shared_ptr<ParallaxBackground> mSkyline;
	std::shared_ptr<Ground> mGround;
	std::shared_ptr<Engine::Sprite> mTitle;
	std::shared_ptr<Engine::Sprite> mInstructions;
	float mMillisecondsToLoad;
	bool mHasLoadedGamePlay;
	bool mIsLoadingResources;
	int mWindowWidth;
	int mWindowHeight;
	bool mSpacePressedBefore;

	std::shared_ptr<Engine::ITextureManager> mTextureManager;
	std::shared_ptr<Engine::IInputManager> mInputManager;
	IGameStateCallback* mGame;
};