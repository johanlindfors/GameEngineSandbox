#include "GamePlayScene.h"
#include "textures/TextureManager.h"
#include "IOC.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;

#define SPRITE_SIZE 20
#define SCREEN_SIZE 20
#define FRAMES_PER_SECOND 15
#define INITIAL_TAIL 5

GamePlayScene::GamePlayScene() 
	: mScreenSizeX(0)
	, mScreenSizeY(0)
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
    
	mApple.Texture = mTextureManager->GetTexture(L"apple.png");
	mApple.Height = 64;
	mApple.Width = 64;
	mApple.Position.X(100.0f);
	mApple.Position.Y(100.0f);

	mSnake.Texture = mTextureManager->GetTexture(EMPTY_TEXTURE_NAME);
}

void GamePlayScene::Unload()
{

}

void GamePlayScene::UpdateScreenSize(int width, int height) 
{
	mScreenSizeX = width;
	mScreenSizeY = height;
	
	mApple.Height = height / SCREEN_SIZE;
	mApple.Width = width / SCREEN_SIZE;
}

void GamePlayScene::HandleInput() 
{
	if (mInputManager->IsKeyDown(40)) {
		mApple.Velocity.Y(1.0f);
		mApple.Velocity.X(0.0f);
	}
	if (mInputManager->IsKeyDown(38)) {
		mApple.Velocity.Y(-1.0f);
		mApple.Velocity.X(0.0f);
	}
	if (mInputManager->IsKeyDown(37)) {
		mApple.Velocity.X(-1.0f);
		mApple.Velocity.Y(0.0f);
	}
	if (mInputManager->IsKeyDown(39)) {
		mApple.Velocity.X(1.0f);
		mApple.Velocity.Y(0.0f);
	}
}

void GamePlayScene::Update(Utilities::StepTimer const& timer)
{
	HandleInput();

	// do updates
	mApple.Position.X(mApple.Position.X() + mApple.Velocity.X());
	mApple.Position.Y(mApple.Position.Y() + mApple.Velocity.Y());
}

void GamePlayScene::Draw(Utilities::StepTimer const& timer)
{
	mSpriteRenderer->DrawSprite(mApple);
}