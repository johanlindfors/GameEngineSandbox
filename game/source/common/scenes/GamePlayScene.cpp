#include "GamePlayScene.h"
#include "textures/TextureManager.h"
#include "IOC.hpp"

using std::make_shared;
using Engine::IInputManager;
using Engine::ISpriteRenderer;
using Engine::ITextureManager;
using Utilities::StepTimer;
using Utilities::IOCContainer;
using Utilities::Vector2;

GamePlayScene::GamePlayScene() 
	: mScreenSizeX(0)
	, mScreenSizeY(0)
	, mApple(make_shared<Apple>(Vector2(3.0f, 10.0f)))
	, mSnake(make_shared<Snake>(Vector2(10.0f, 10.0f)))
{
	ID = "GamePlayScene";
}

GamePlayScene::~GamePlayScene()
{
	Unload();
}

void GamePlayScene::Load()
{
	mTextureManager = IOCContainer::Instance().Resolve<ITextureManager>();
    mSpriteRenderer = IOCContainer::Instance().Resolve<ISpriteRenderer>();
	mInputManager = IOCContainer::Instance().Resolve<IInputManager>();
    
	mApple->SetTexture(mTextureManager->GetTexture(L"apple.png"));
	mSnake->SetTexture(mTextureManager->GetTexture(EMPTY_TEXTURE_NAME));
}

void GamePlayScene::Unload()
{
	mApple.reset();
	mSnake.reset();
}

void GamePlayScene::UpdateScreenSize(int width, int height) 
{
	mScreenSizeX = width;
	mScreenSizeY = height;

}

void GamePlayScene::Update(StepTimer const& timer)
{
	mSnake->HandleInput(mInputManager);

	// do updates
	mApple->Update(mScreenSizeX, mScreenSizeY);
	mSnake->Update(mScreenSizeX, mScreenSizeY);
}

void GamePlayScene::Draw(StepTimer const& timer)
{
	mApple->Draw(mSpriteRenderer);
	mSnake->Draw(mSpriteRenderer);
}
