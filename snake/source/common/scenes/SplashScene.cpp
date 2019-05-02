#include "SplashScene.h"
#include "textures/TextureManager.h"
#include "IOC.hpp"
#include "scenes/ISceneManager.h"
#include "GamePlayScene.h"
#include "game/IGameStateCallback.h"
#include "textures/ITextureManager.h"
#include "rendering/ISpriteRenderer.h"
#include "rendering/Sprite.h"
#include "IStepTimer.h"

using namespace std;
using namespace Engine;
using namespace Utilities;

SplashScene::SplashScene(IGameStateCallback* gameCallback)
	: mSprite(make_shared<Sprite>())
	, mMillisecondsToLoad(1000.0f)
	, hasLoadedGamePlay(false)
	, mGame(gameCallback)
{
	ID = typeid(SplashScene).name();
}

SplashScene::~SplashScene()
{

}

void SplashScene::Load()
{
	mTextureManager = IOCContainer::Instance().Resolve<ITextureManager>();
    mSpriteRenderer = IOCContainer::Instance().Resolve<ISpriteRenderer>();
    
	vector<wstring> filenames;
	filenames.emplace_back(L"coderox.png");
	filenames.emplace_back(L"apple.png");
	filenames.emplace_back(L"snake.png");
	filenames.emplace_back(L"gameover/background.png");
	filenames.emplace_back(L"gameover/text.png");
	filenames.emplace_back(L"pause/background.png");
	filenames.emplace_back(L"pause/text.png");
	mTextureManager->LoadTextures(vector<wstring>(filenames));

	mSprite->Texture = mTextureManager->GetTexture(L"coderox.png");
}

void SplashScene::Unload()
{

}

void SplashScene::UpdateScreenSize(int width, int height) 
{
	mSprite->Height = height;
	mSprite->Width = width;
	mSprite->Position = { 0.0f, 0.0f };

}

void SplashScene::Update(shared_ptr<IStepTimer> timer)
{
	mMillisecondsToLoad -= static_cast<float>((timer->GetElapsedSeconds() * 1000.0f));
	if (mMillisecondsToLoad <= 0) {
		auto sceneManager = IOCContainer::Instance().Resolve<ISceneManager>();
		if (!hasLoadedGamePlay) {
			mGame->GoToState(GameState::GamePlay);
			hasLoadedGamePlay = true;
		}
	}
}

void SplashScene::Draw(shared_ptr<IStepTimer> /*timer*/)
{
	if (mSpriteRenderer) {
		mSpriteRenderer->DrawSprite(mSprite);
	}
}