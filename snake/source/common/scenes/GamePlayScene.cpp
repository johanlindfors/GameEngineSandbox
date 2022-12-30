#include "GamePlayScene.h"
#include "resources/IResourceManager.h"
#include "utilities/IOC.hpp"
#include "objects/Snake.h"
#include "objects/Apple.h"
#include "objects/PointCollider.h"
#include "renderers/ISpriteRenderer.h"
#include "input/IInputManager.h"
#include "game/IGameStateCallback.h"
#include "utilities/MathHelper.h"
#include "game/GameDefines.h"
#include "renderers/Sprite.h"

using namespace std;
using namespace Engine;
using namespace Utilities;

GamePlayScene::GamePlayScene(IGameStateCallback* gameCallback)
	: mApple(make_shared<Apple>(Point<int>(SCREEN_SIZE / 4, SCREEN_SIZE / 4)))
	, mSnake(make_shared<Snake>(Point<int>(SCREEN_SIZE / 2, SCREEN_SIZE / 2)))
	, mCollider(make_shared<PointCollider>())
	, mScreenSizeX(0)
	, mScreenSizeY(0)
	, mGame(gameCallback)
	, mSpacePressedBefore(false)
{
	ID = typeid(GamePlayScene).name();
}

void GamePlayScene::Load()
{
	auto resourceManager = IOCContainer::Instance().Resolve<IResourceManager>();
	mInputManager = IOCContainer::Instance().Resolve<IInputManager>();

	mApple->SetTexture(resourceManager->GetTexture("apple.png"));
	mSnake->SetTexture(resourceManager->GetTexture("snake.png"));
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

		if (mCollider->Collides(
			Point<int>(static_cast<int>(mSnake->GetSprite()->Position.X),
					   static_cast<int>(mSnake->GetSprite()->Position.Y)), 
			Point<int>(static_cast<int>(mApple->GetSprite()->Position.X),
		    		   static_cast<int>(mApple->GetSprite()->Position.Y))

		))
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

void GamePlayScene::Draw(shared_ptr<IRenderer> renderer)
{
	auto spriteRenderer = static_pointer_cast<ISpriteRenderer>(renderer);
	if(spriteRenderer) {
		mApple->Draw(spriteRenderer);
		mSnake->Draw(spriteRenderer);
	}
}
