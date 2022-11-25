#pragma once
#include "scenes/GameScene.h"

class IGameStateCallback;
class Bird;
class VectorCollider;

namespace Engine 
{
	class ITextureManager;
	class ISpriteRenderer;
	class IInputManager;
	class Sprite;
}

class GamePlayScene : public Engine::GameScene 
{
public:
    GamePlayScene(IGameStateCallback* gameCallback);
    ~GamePlayScene();

	// Engine::GameScene
    void Load() override;
	void Unload() override;
	void UpdateScreenSize(int width, int height) override;
	void Update(std::shared_ptr<Utilities::IStepTimer> timer) override;
	void Draw(std::shared_ptr<Utilities::IStepTimer> timer) override;

private:
	std::shared_ptr<Engine::Sprite> mBackground;
	std::shared_ptr<VectorCollider> mCollider;

	std::shared_ptr<Engine::ITextureManager> mTextureManager;
    std::shared_ptr<Engine::ISpriteRenderer> mSpriteRenderer;
	std::shared_ptr<Engine::IInputManager> mInputManager;
	int mScreenSizeX;
	int mScreenSizeY;
	IGameStateCallback* mGame;
	bool mSpacePressedBefore;
};