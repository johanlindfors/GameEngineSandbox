#include "GameOverScene.h"
#include "textures/TextureManager.h"
#include "scenes/ISceneManager.h"
#include "input/IInputManager.h"
#include "renderer/SpriteRenderer.h"
#include "renderer/Sprite.h"
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
	mTextureManager = IOCContainer::Instance().Resolve<ITextureManager>();
	mInputManager = IOCContainer::Instance().Resolve<IInputManager>();

	mBackground->Texture = mTextureManager->GetTexture(L"gameover/background.png");
    mText->Texture = mTextureManager->GetTexture(L"gameover/text.png");
}

void GameOverScene::Unload() { }

void GameOverScene::UpdateScreenSize(int width, int height) 
{
	mBackground->Height = height;
	mBackground->Width = width;
	mBackground->Position = { 0, 0 };

	mText->Height = height / 4;
	mText->Width = width / 4;
	mText->Position = { width / 2 - mText->Width / 2, height / 2 - mText->Height / 2 };
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

void GameOverScene::Draw(shared_ptr<ISpriteRenderer> renderer)
{
	if (renderer) {
		renderer->DrawSprite(mBackground);
        renderer->DrawSprite(mText);
	}
}
