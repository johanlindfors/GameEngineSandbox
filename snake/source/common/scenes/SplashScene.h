#pragma once
#include "scenes/GameScene.h"
#include <memory>
#include <queue>

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
    void Load();
	void Unload();
	void UpdateScreenSize(int width, int height);
	void Update(std::shared_ptr<Utilities::IStepTimer> timer);
	void Draw(std::shared_ptr<Utilities::IStepTimer> timer);

private:
	std::shared_ptr<Engine::Sprite> mSprite;
	float mMillisecondsToLoad;
	bool hasLoadedGamePlay;
	bool isLoadingResources;
	std::queue<std::wstring> mResourcesToLoad;

	std::shared_ptr<Engine::ITextureManager> mTextureManager;
    std::shared_ptr<Engine::ISpriteRenderer> mSpriteRenderer;
	IGameStateCallback* mGame;
};