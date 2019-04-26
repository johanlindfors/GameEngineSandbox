#include "GameOverScene.h"
#include "textures/TextureManager.h"
#include "scenes/ISceneManager.h"
#include "input/IInputManager.h"
#include "sprites/SpriteRenderer.h"
#include "sprites/Sprite.h"
#include "IOC.hpp"
#include "IGameStateCallback.h"

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

GameOverScene::~GameOverScene()
{

}

void GameOverScene::Load()
{
	mTextureManager = IOCContainer::Instance().Resolve<ITextureManager>();
    mSpriteRenderer = IOCContainer::Instance().Resolve<ISpriteRenderer>();
	mInputManager = IOCContainer::Instance().Resolve<IInputManager>();

	mBackground->Texture = mTextureManager->GetTexture(L"gameover-background.png");
    mText->Texture = mTextureManager->GetTexture(L"gameover-text.png");
}

void GameOverScene::Unload()
{

}

void GameOverScene::UpdateScreenSize(int width, int height) 
{
	mBackground->Height = height;
	mBackground->Width = width;
	mBackground->Position = { 0.0f, 0.0f };

	mText->Height = static_cast<int>(height / 4.0f);
	mText->Width = static_cast<int>(width / 4.0f);
	mText->Position = { width / 2.0f - mText->Width / 2.0f, height / 2.0f - mText->Height / 2.0f };
}

void GameOverScene::HandleInput() 
{
	if (mInputManager->IsKeyDown(32)) // Spacebar
	{
		mGame->GoToState(GameState::GamePlay);
	}
}

void GameOverScene::Update(shared_ptr<IStepTimer> timer)
{
	HandleInput();
}

void GameOverScene::Draw(shared_ptr<IStepTimer> /*timer*/)
{
	if (mSpriteRenderer) {
		mSpriteRenderer->DrawSprite(mBackground);
        mSpriteRenderer->DrawSprite(mText);
	}
}