#pragma once
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
}

class InstructionsScene : public Engine::GameScene 
{
public:
	InstructionsScene(IGameStateCallback* gameCallback);
    ~InstructionsScene() = default;

	// Engine::GameScene
    void load() override;
	void unload() override;
	void updateScreenSize(int width, int height) override;
	void update(std::shared_ptr<Utilities::IStepTimer> timer) override;
	void draw(std::shared_ptr<Engine::IRenderer> renderer) override;

private:
	void handleInput();
    
    int mWindowWidth;
	int mWindowHeight;
	bool mSpacePressedBefore;
	std::shared_ptr<Engine::Sprite> mInstructions;
	std::shared_ptr<Engine::Sprite> mGetReady;
	std::shared_ptr<Utilities::ITweenEngine> mTweenEngine;
	std::shared_ptr<Engine::IInputManager> mInputManager;
	IGameStateCallback* mGame;
};