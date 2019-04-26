#include "GameOverScene.h"
#include "textures/TextureManager.h"
#include "IOC.hpp"
#include "scenes/ISceneManager.h"
#include "sprites/Sprite.h"

using namespace std;
using namespace Engine;
using namespace Utilities;

GameOverScene::GameOverScene()
	: mBackground(make_shared<Sprite>())	
	, mText(make_shared<Sprite>())
{
	ID = "GameOverScene";
}

GameOverScene::~GameOverScene()
{

}

void GameOverScene::Load()
{
	mTextureManager = IOCContainer::Instance().Resolve<ITextureManager>();
    mSpriteRenderer = IOCContainer::Instance().Resolve<ISpriteRenderer>();

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

	mText->Height = height / 4.0f;
	mText->Width = width / 4.0f;
	mText->Position = { width / 2.0f - mText->Width / 2.0f, height / 2.0f - mText->Height / 2.0f };
}

void GameOverScene::Update(shared_ptr<IStepTimer> timer)
{

}

void GameOverScene::Draw(shared_ptr<IStepTimer> /*timer*/)
{
	if (mSpriteRenderer) {
		mSpriteRenderer->DrawSprite(mBackground);
        mSpriteRenderer->DrawSprite(mText);
	}
}