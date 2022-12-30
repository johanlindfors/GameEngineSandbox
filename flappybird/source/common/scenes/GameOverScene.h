#pragma once
#include "scenes/GameScene.h"

class IGameStateCallback;
class ScoreSystem;

namespace Utilities
{
	class IStepTimer;
	class ITweenEngine;
}

namespace Engine
{
	struct Sprite;
	class ITextureManager;
	class IRenderer;
	class IInputManager;
	class FontRenderer;
}

class GameOverScene : public Engine::GameScene 
{
public:
	GameOverScene(IGameStateCallback* gameCallback);
    ~GameOverScene();

	// Engine::GameScene
    void Load() override;
	void Unload() override;
	void UpdateScreenSize(int width, int height) override;
	void Update(std::shared_ptr<Utilities::IStepTimer> timer) override;
	void Draw(std::shared_ptr<Engine::IRenderer> renderer) override;

private:
	void HandleInput();

	std::shared_ptr<Engine::Sprite> mGameOverText;
    std::shared_ptr<Engine::Sprite> mScoreBoard;
	std::shared_ptr<Engine::Sprite> mMedal;
	std::shared_ptr<Engine::Sprite> mButton;

	std::shared_ptr<Engine::FontRenderer> mFontRenderer;
	std::shared_ptr<Utilities::ITweenEngine> mTweenEngine;
  	std::shared_ptr<Engine::IInputManager> mInputManager;
	IGameStateCallback* mGame;
	std::shared_ptr<ScoreSystem> mScoreSystem;
};