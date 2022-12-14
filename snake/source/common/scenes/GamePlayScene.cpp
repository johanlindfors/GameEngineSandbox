#include "GamePlayScene.h"
#include "respirces/IResourceManager.h"
#include "utilities/IOC.hpp"
#include "objects/Snake.h"
#include "objects/Apple.h"
#include "objects/PointCollider.h"
#include "renderer/ISpriteRenderer.h"
#include "input/IInputManager.h"
#include "game/IGameStateCallback.h"
#include "utilities/MathHelper.h"
#include "game/GameDefines.h"
#include "renderer/Sprite.h"

using std::make_shared;
using std::shared_ptr;
using Engine::IInputManager;
using Engine::ISpriteRenderer;
using Engine::IResourceManager;
using Utilities::IStepTimer;
using Utilities::IOCContainer;
using Utilities::Point;

GamePlayScene::GamePlayScene(IGameStateCallback* gameCallback)
	: mApple(make_shared<Apple>(Point<float>(SCREEN_SIZE / 4, SCREEN_SIZE / 4)))
	, mSnake(make_shared<Snake>(Point<float>(SCREEN_SIZE / 2, SCREEN_SIZE / 2)))
	, mCollider(make_shared<PointCollider>())
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
	mResourceManager = IOCContainer::Instance().Resolve<IResourceManager>();
	mInputManager = IOCContainer::Instance().Resolve<IInputManager>();

	mApple->SetTexture(mResourceManager->GetTexture(L"apple.png"));
	mSnake->SetTexture(mResourceManager->GetTexture(L"snake.png"));
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
	auto const spacePressed = mInputManager->IsKeyDown(32);
	if (mGame->GetCurrentState() == GameState::GamePlay) {
		mSnake->HandleInput(mInputManager);

		// do updates
		mApple->Update(mScreenSizeX, mScreenSizeY);
		mSnake->Update(mScreenSizeX, mScreenSizeY, mGame);

		if (mCollider->Collides(mSnake->GetSprite()->Position, mApple->GetSprite()->Position))
		{
			mApple->Reset(mSnake, mCollider);
			mSnake->IncreaseLength();
		}

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
	mApple->Draw(renderer);
	mSnake->Draw(renderer);
}
