#include "GamePlayScene.h"
#include "textures/TextureManager.h"
#include "IOC.hpp"
#include "objects/Bird.h"
// #include "objects/VectorCollider.h"
#include "textures/ITextureManager.h"
#include "renderer/ISpriteRenderer.h"
#include "input/IInputManager.h"
#include "game/IGameStateCallback.h"
#include "MathHelper.h"
#include "game/GameDefines.h"
#include "renderer/Sprite.h"
#include "objects/ParallaxBackground.h"

using namespace std;
using Engine::IInputManager;
using Engine::ISpriteRenderer;
using Engine::ITextureManager;
using Utilities::IStepTimer;
using Utilities::IOCContainer;
using Utilities::Vector2;

GamePlayScene::GamePlayScene(IGameStateCallback* gameCallback)
	: mBackground(make_shared<Engine::Sprite>())
	, mSkyline(make_unique<ParallaxBackground>())
	, mBird(make_shared<Bird>(Vector2(100,100)))
	// , mCollider(make_shared<VectorCollider>())
	, mScreenSizeX(0)
	, mScreenSizeY(0)
	, mGame(gameCallback)
	, mSpacePressedBefore(false)
{
	ID = typeid(GamePlayScene).name();
}

GamePlayScene::~GamePlayScene()
{

}

void GamePlayScene::Load()
{
	mTextureManager = IOCContainer::Instance().Resolve<ITextureManager>();
	mInputManager = IOCContainer::Instance().Resolve<IInputManager>();

	mBackground->Texture = mTextureManager->GetTexture(L"sky.png");
	mBackground->Width = 288;
	mBackground->Height = 505;

	mBird->SetTexture(mTextureManager->GetTexture(L"bird.png"));
	mBird->GetSprite()->Width = 30;
	mBird->GetSprite()->Height = 30;
}

void GamePlayScene::Unload()
{
	mBackground.reset();
}

void GamePlayScene::UpdateScreenSize(int width, int height)
{
	mScreenSizeX = width;
	mScreenSizeY = height;
}

void GamePlayScene::Update(shared_ptr<IStepTimer> timer)
{
	auto const spacePressed = mInputManager->IsKeyDown(32);
	if (mGame->GetCurrentState() == GameState::GamePlay) {
		//mBird->HandleInput(mInputManager);

		// do updates
		mBird->Update(timer);

		// if (mCollider->Collides(mSnake->GetSprite()->Position, mApple->GetSprite()->Position))
		// {

		// }

		if (spacePressed && !mSpacePressedBefore)
		{
			mGame->GoToState(GameState::Pause);
		}
	}
	else {
		if (spacePressed && !mSpacePressedBefore)
		{
			mGame->GoToState(GameState::GamePlay);
		}
	}
	mSpacePressedBefore = spacePressed;
}

void GamePlayScene::Draw(shared_ptr<ISpriteRenderer> renderer)
{
	renderer->DrawSprite(mBackground);
	mBird->Draw(renderer);
}
