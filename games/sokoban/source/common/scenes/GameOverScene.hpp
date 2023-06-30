#pragma once

// stl
#include <string>

// engine
#include "scenes/GameScene.hpp"

class IGameStateCallback;

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
    ~GameOverScene() = default;

	// Engine::GameScene
    void load() override { };
	void unload() override { };
	void updateScreenSize(int width, int height) override { };
	void update(std::shared_ptr<Utilities::IStepTimer> timer) override { };
	void draw(std::shared_ptr<Engine::IRenderer> renderer) override;

private:
	std::string mGameOverText;
	std::shared_ptr<Engine::FontRenderer> mFontRenderer;
	std::shared_ptr<Utilities::ITweenEngine> mTweenEngine;
  	std::shared_ptr<Engine::IInputManager> mInputManager;
	IGameStateCallback* mGame;
};
