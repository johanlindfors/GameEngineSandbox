#pragma once
#include "scenes/GameScene.h"

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
	class ISpriteRenderer;
	class IInputManager;
}

class InstructionsScene : public Engine::GameScene 
{
public:
	InstructionsScene(IGameStateCallback* gameCallback);
    ~InstructionsScene() = default;

	// Engine::GameScene
    void Load() override;
	void Unload() override;
	void UpdateScreenSize(int width, int height) override;
	void Update(std::shared_ptr<Utilities::IStepTimer> timer) override;
	void Draw(std::shared_ptr<Engine::ISpriteRenderer> renderer) override;

private:
	void HandleInput();
    
    int mWindowWidth;
	int mWindowHeight;
	bool mSpacePressedBefore;
	std::shared_ptr<Engine::Sprite> mInstructions;
	std::shared_ptr<Utilities::ITweenEngine> mTweenEngine;
	std::shared_ptr<Engine::IInputManager> mInputManager;
	IGameStateCallback* mGame;
};