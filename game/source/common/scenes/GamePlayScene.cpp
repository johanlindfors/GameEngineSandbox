#include "GamePlayScene.h"
#include "textures/TextureManager.h"
#include "IOC.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;

GamePlayScene::GamePlayScene() 
	: mScreenSizeX(0.0f)
	, mScreenSizeY(0.0f)
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
	mScreenSizeX = width;
	mScreenSizeY = height;
}

void GamePlayScene::Update(Utilities::StepTimer const& timer)
{
	// handle input
	if (mInputManager->IsKeyDown(40)) {
		mApple.mVelocityY = 1.0f; 
		mApple.mVelocityX = 0.0f;
	}
	if (mInputManager->IsKeyDown(38)) {
		mApple.mVelocityY = -1.0f;
		mApple.mVelocityX = 0.0f;
	}
	if (mInputManager->IsKeyDown(37)) {
		mApple.mVelocityX = -1.0f;
		mApple.mVelocityY = 0.0f;
	}
	if (mInputManager->IsKeyDown(39)) {
		mApple.mVelocityX = 1.0f;
		mApple.mVelocityY = 0.0f;
	}

	// do updates
	mApple.mPositionX = static_cast<int>(mApple.mPositionX + mApple.mVelocityX);
	mApple.mPositionY = static_cast<int>(mApple.mPositionY + mApple.mVelocityY);
}

void GamePlayScene::Draw(Utilities::StepTimer const& timer)
{
	mSpriteRenderer->DrawSprite(mApple);
}