#include "GamePlayScene.h"
#include "textures/TextureManager.h"
#include "IOC.hpp"
#include "objects/Snake.h"
#include "objects/Apple.h"
#include "objects/SpriteCollider.h"
#include "textures/ITextureManager.h"
#include "rendering/ISpriteRenderer.h"
#include "input/IInputManager.h"
#include "game/IGameStateCallback.h"
#include "MathHelper.h"

using std::make_shared;
using std::shared_ptr;
using Engine::IInputManager;
using Engine::ISpriteRenderer;
using Engine::ITextureManager;
using Utilities::IStepTimer;
using Utilities::IOCContainer;
using Utilities::Vector2;

GamePlayScene::GamePlayScene(IGameStateCallback* gameCallback)
	: mScreenSizeX(0)
	, mScreenSizeY(0)
	, mApple(make_shared<Apple>(Vector2(3.0f, 10.0f)))
	, mSnake(make_shared<Snake>(Vector2(10.0f, 10.0f)))
	, mSpriteCollider(make_shared<SpriteCollider>())
	, mGame(gameCallback)
	, mSpacePressedBefore(false)
{
	ID = typeid(GamePlayScene).name();
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
	mSnake->SetTexture(mTextureManager->GetTexture(L"snake.png"));
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

void GamePlayScene::Update(shared_ptr<IStepTimer> /*timer*/)
{
	bool spacePressed = mInputManager->IsKeyDown(32);
	if (mGame->GetCurrentState() == GameState::GamePlay) {
		mSnake->HandleInput(mInputManager);

		if (mSpriteCollider->CollidesOnPosition(mSnake->GetSprite(), mApple->GetSprite()))
		{
			mApple->Reset();
			mSnake->IncreaseLength();
		}

		// do updates
		mApple->Update(mScreenSizeX, mScreenSizeY);
		mSnake->Update(mScreenSizeX, mScreenSizeY, mGame);

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

void GamePlayScene::Draw(shared_ptr<IStepTimer> /*timer*/)
{
	mApple->Draw(mSpriteRenderer);
	mSnake->Draw(mSpriteRenderer);
}
