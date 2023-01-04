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
	class IRenderer;
	class IInputManager;
}

class GameOverScene : public Engine::GameScene 
{
public:
	GameOverScene(IGameStateCallback* gameCallback);
    ~GameOverScene();

	// Engine::GameScene
    void load() override;
	void unload() override;
	void updateScreenSize(int width, int height) override;
	void update(std::shared_ptr<Utilities::IStepTimer> timer) override;
	void draw(std::shared_ptr<Engine::IRenderer> renderer) override;

private:
	void handleInput();

	std::shared_ptr<Engine::Sprite> mBackground;
    std::shared_ptr<Engine::Sprite> mText;
	std::shared_ptr<Engine::IInputManager> mInputManager;
	IGameStateCallback* mGame;
};