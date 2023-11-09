#pragma once
#include "scenes/GameScene.hpp"

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
	GameOverScene(IGameStateCallback *gameCallback);
	~GameOverScene();

	// Engine::GameScene
	void load() override;
	void unload() override;
	void updateScreenSize(int width, int height) override;
	void update(std::shared_ptr<Utilities::IStepTimer> timer) override;
	void draw(std::shared_ptr<Engine::IRenderer> renderer) override;

private:
	void handleInput();

	std::shared_ptr<Engine::Sprite> mGameOverText;
	std::shared_ptr<Engine::Sprite> mScoreBoard;
	std::shared_ptr<Engine::Sprite> mMedal;
	std::shared_ptr<Engine::Sprite> mButton;

	std::shared_ptr<Engine::FontRenderer> mFontRenderer;
	std::shared_ptr<Utilities::ITweenEngine> mTweenEngine;
	std::shared_ptr<Engine::IInputManager> mInputManager;
	IGameStateCallback *mGame;
	std::shared_ptr<ScoreSystem> mScoreSystem;
};