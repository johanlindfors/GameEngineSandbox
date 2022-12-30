#include "GameOverScene.h"
#include "resources/ResourceManager.h"
#include "scenes/ISceneManager.h"
#include "input/IInputManager.h"
#include "renderers/SpriteRenderer.h"
#include "renderers/Sprite.h"
#include "utilities/IOC.hpp"
#include "game/IGameStateCallback.h"

using namespace std;
using namespace Engine;
using namespace Utilities;

GameOverScene::GameOverScene(IGameStateCallback* gameCallback)
	: mBackground(make_shared<Sprite>())	
	, mText(make_shared<Sprite>())
	, mGame(gameCallback)	
{
	ID = typeid(GameOverScene).name();
}

GameOverScene::~GameOverScene() { }

void GameOverScene::Load()
{
	auto resourceManager = IOCContainer::Instance().Resolve<IResourceManager>();
	mInputManager = IOCContainer::Instance().Resolve<IInputManager>();

	mBackground->Texture = resourceManager->GetTexture("gameover/background.png");
    mText->Texture = resourceManager->GetTexture("gameover/text.png");
}

void GameOverScene::Unload() { }

void GameOverScene::UpdateScreenSize(int width, int height) 
{
	mBackground->Height = height;
	mBackground->Width = width;
	mBackground->Position = { 0, 0 };

	mText->Height = height / 4;
	mText->Width = width / 4;
	mText->Position = { static_cast<float>(width / 2 - mText->Width / 2), 
						static_cast<float>(height / 2 - mText->Height / 2) };
}

void GameOverScene::HandleInput() 
{
	if (mInputManager->IsKeyDown(32)) // SpaceBar
	{
		mGame->GoToState(GameState::GamePlay);
	}
}

void GameOverScene::Update(shared_ptr<IStepTimer> timer)
{
	HandleInput();
}

void GameOverScene::Draw(shared_ptr<IRenderer> renderer)
{
	auto spriteRenderer = static_pointer_cast<ISpriteRenderer>(renderer);
	if (spriteRenderer) {
		spriteRenderer->DrawSprite(mBackground);
        spriteRenderer->DrawSprite(mText);
	}
}
