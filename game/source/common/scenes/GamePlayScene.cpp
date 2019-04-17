#include "GamePlayScene.h"
#include "textures/TextureManager.h"
#include "IOC.hpp"

using namespace std;

GamePlayScene::GamePlayScene() 
{
	ID = "GamePlayScene";
}

GamePlayScene::~GamePlayScene()
{

}

void GamePlayScene::Load()
{
	mTextureManager = IOCContainer::Instance().Resolve<ITextureManager>();
    mSpriteRenderer = IOCContainer::Instance().Resolve<ISpriteRenderer>();
	mInputManager = IOCContainer::Instance().Resolve<IInputManager>();
    
	mApple.mTexture = mTextureManager->GetTexture(L"apple.png");
	mApple.mHeight = 64.0f;
	mApple.mWidth = 64.0f;
	mApple.mPositionX = 100.0f;
	mApple.mPositionY = 100.0f;
}

void GamePlayScene::Unload()
{

}

void GamePlayScene::UpdateScreenSize(int width, int height) 
{

}

void GamePlayScene::Update(Utilities::StepTimer const& timer)
{
	if (mInputManager->IsKeyDown(40)) {
		mApple.mPositionY += 1.0f;
	}
}

void GamePlayScene::Draw(Utilities::StepTimer const& timer)
{
	mSpriteRenderer->DrawSprite(mApple);
}