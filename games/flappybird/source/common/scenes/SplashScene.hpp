#pragma once
#include "scenes/GameScene.hpp"
#include <memory>
#include <queue>

class IGameStateCallback;
class ParallaxBackground;
class Bird;
class Ground;

namespace Engine
{
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
	SplashScene(IGameStateCallback *gameCallback);
	~SplashScene();

	// Engine::GameScene
	void load() override;
	void unload() override;
	void updateScreenSize(int width, int height) override;
	void update(std::shared_ptr<Utilities::IStepTimer> timer) override;
	void draw(std::shared_ptr<Engine::IRenderer> renderer) override;

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

	std::shared_ptr<Engine::IInputManager> mInputManager;
	IGameStateCallback *mGame;
};