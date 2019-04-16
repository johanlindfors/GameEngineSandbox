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
    
	//vector<wstring> filenames;
	//filenames.emplace_back(L"apple.png");
	//mTextureManager->LoadTextures(vector<wstring>(filenames));

	mApple.mTexture = mTextureManager->GetTexture(L"apple.png");
}

void GamePlayScene::Unload()
{

}

void GamePlayScene::UpdateScreenSize(int width, int height) 
{

}

void GamePlayScene::Update(Utilities::StepTimer const& timer)
{
	mApple.mHeight = 64.0f;
	mApple.mWidth = 64.0f;
	mApple.mPositionX = 100.0f;
	mApple.mPositionY = 100.0f;
}

void GamePlayScene::Draw(Utilities::StepTimer const& timer)
{
	mSpriteRenderer->DrawSprite(mApple);
}