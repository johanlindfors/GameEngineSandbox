#include "SplashScene.h"
#include "textures/TextureManager.h"
#include "IOC.hpp"
#include "scenes/ISceneManager.h"
#include "GamePlayScene.h"

using namespace std;

SplashScene::SplashScene()
	: mMillisecondsToLoad(1000.0f)
	, hasLoadedGamePlay(false)
{
	ID = "SplashScene";
}

SplashScene::~SplashScene()
{

}

void SplashScene::Load()
{
	mTextureManager = IOCContainer::Instance().Resolve<ITextureManager>();
    mSpriteRenderer = IOCContainer::Instance().Resolve<ISpriteRenderer>();
    
	vector<wstring> filenames;
	filenames.emplace_back(L"splash.png");
	filenames.emplace_back(L"apple.png");
	mTextureManager->LoadTextures(vector<wstring>(filenames));

	mSprite.mTexture = mTextureManager->GetTexture(L"splash.png");
}

void SplashScene::Unload()
{

}

void SplashScene::UpdateScreenSize(int width, int height) 
{
	mSprite.mHeight = height;
	mSprite.mWidth = width;
	mSprite.mPositionX = 0.0f;
	mSprite.mPositionY = 0.0f;

}

void SplashScene::Update(Utilities::StepTimer const& timer)
{
	if (hasLoadedGamePlay) {
		return;
	}
	mMillisecondsToLoad -= (timer.GetElapsedSeconds() * 1000.0f);
	if (mMillisecondsToLoad <= 0) {
		auto sceneManager = IOCContainer::Instance().Resolve<ISceneManager>();
		sceneManager->AddScene(make_shared<GamePlayScene>());
		//sceneManager->RemoveScene(ID);
		hasLoadedGamePlay = true;
	}
}

void SplashScene::Draw(Utilities::StepTimer const& timer)
{
	if (mSpriteRenderer) {
		mSpriteRenderer->DrawSprite(mSprite);
	}
}