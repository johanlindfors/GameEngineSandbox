#include "SplashScene.h"
#include "textures/TextureManager.h"
#include "IOC.hpp"

using namespace std;

SplashScene::SplashScene() 
{

}

SplashScene::~SplashScene()
{

}

void SplashScene::Load()
{
	mTextureManager = IOCContainer::Instance().Resolve<ITextureManager>();
    mSpriteRenderer = IOCContainer::Instance().Resolve<ISpriteRenderer>();
    
	vector<wstring> filenames;
	filenames.emplace_back(L"bird.png");
	filenames.emplace_back(L"file2.png");
	mTextureManager->LoadTextures(vector<wstring>(filenames));

	mSprite.mTexture = mTextureManager->GetTexture(L"bird.png");
}

void SplashScene::Unload()
{

}

void SplashScene::UpdateScreenSize(int width, int height) 
{

}

void SplashScene::Update(Utilities::StepTimer const& timer)
{
	mSprite.mHeight = 24.0f;
	mSprite.mWidth = 34.0f;
	mSprite.mPositionX = 100.0f;
	mSprite.mPositionY = 100.0f;
}

void SplashScene::Draw(Utilities::StepTimer const& timer)
{
	mSpriteRenderer->DrawSprite(mSprite);
}