#pragma once
#include "scenes/GameScene.h"

class IGameStateCallback;

namespace Utilities
{
	class IStepTimer;
}

namespace Engine
{
	struct Sprite;
	class ITextureManager;
	class ISpriteRenderer;
	class IInputManager;
}

class GameOverScene : public Engine::GameScene 
{
public:
	GameOverScene(IGameStateCallback* gameCallback);
    ~GameOverScene();
    void Load();
	void Unload();
	void UpdateScreenSize(int width, int height);
	void Update(std::shared_ptr<Utilities::IStepTimer> timer);
	void Draw(std::shared_ptr<Utilities::IStepTimer> timer);

private:
	void HandleInput();

	std::shared_ptr<Engine::Sprite> mBackground;
    std::shared_ptr<Engine::Sprite> mText;
	std::shared_ptr<Engine::ITextureManager> mTextureManager;
    std::shared_ptr<Engine::ISpriteRenderer> mSpriteRenderer;
	std::shared_ptr<Engine::IInputManager> mInputManager;
	IGameStateCallback* mGame;
};