#include "PauseScene.h"
#include "textures/TextureManager.h"
#include "IOC.hpp"
#include "scenes/ISceneManager.h"
#include "sprites/Sprite.h"

using namespace std;
using namespace Engine;
using namespace Utilities;

PauseScene::PauseScene()
	: mBackground(make_shared<Sprite>())
	, mText(make_shared<Sprite>())
{
	ID = "PauseScene";
}

PauseScene::~PauseScene()
{

}

void PauseScene::Load()
{
	mTextureManager = IOCContainer::Instance().Resolve<ITextureManager>();
    mSpriteRenderer = IOCContainer::Instance().Resolve<ISpriteRenderer>();

	mBackground->Texture = mTextureManager->GetTexture(L"pause_background.png");
    mText->Texture = mTextureManager->GetTexture(L"pause_text.png");
}

void PauseScene::Unload()
{

}

void PauseScene::UpdateScreenSize(int width, int height) 
{
	mBackground->Height = height;
	mBackground->Width = width;
	mBackground->Position = { 0.0f, 0.0f };
}

void PauseScene::Update(shared_ptr<IStepTimer> timer)
{

}

void PauseScene::Draw(shared_ptr<IStepTimer> /*timer*/)
{
	if (mSpriteRenderer) {
		mSpriteRenderer->DrawSprite(mBackground);
        mSpriteRenderer->DrawSprite(mText);
	}
}