#pragma once
#include "scenes/GameScene.hpp"

class IGameStateCallback;
class Map;
class Player;

namespace Utilities
{
	class IStepTimer;
}

namespace Engine
{
	struct Sprite;
	class ITextureManager;
	class IRenderer;
	class IInputManager;
	class FontRenderer;
}

class GamePlayScene : public Engine::GameScene 
{
public:
	GamePlayScene(IGameStateCallback* gameCallback);
    ~GamePlayScene();

	// Engine::GameScene
    void load() override;
	void unload() override;
	void updateScreenSize(int width, int height) override;
	void update(std::shared_ptr<Utilities::IStepTimer> timer) override;
	void draw(std::shared_ptr<Engine::IRenderer> renderer) override;

private:
	void handleInput();

	std::unique_ptr<Map> mMap;
	std::unique_ptr<Player> mPlayer;
	std::shared_ptr<Engine::FontRenderer> mFontRenderer;
  	std::shared_ptr<Engine::IInputManager> mInputManager;
	IGameStateCallback* mGame;
};