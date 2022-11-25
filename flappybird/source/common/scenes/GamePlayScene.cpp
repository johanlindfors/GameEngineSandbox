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

using std::make_shared;
using std::shared_ptr;
using Engine::IInputManager;
using Engine::ISpriteRenderer;
using Engine::ITextureManager;
using Utilities::IStepTimer;
using Utilities::IOCContainer;
using Utilities::Vector2;

GamePlayScene::GamePlayScene(IGameStateCallback* gameCallback)
	: mBackground(make_shared<Engine::Sprite>())
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
	mSpriteRenderer = IOCContainer::Instance().Resolve<ISpriteRenderer>();
	mInputManager = IOCContainer::Instance().Resolve<IInputManager>();

	mBackground->Texture = mTextureManager->GetTexture(L"background.png");
	mBackground->Width = 288;
	mBackground->Height = 505;
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

void GamePlayScene::Update(shared_ptr<IStepTimer> /*timer*/)
{
	auto const spacePressed = mInputManager->IsKeyDown(32);
	if (mGame->GetCurrentState() == GameState::GamePlay) {
		//mBird->HandleInput(mInputManager);

		// do updates
		//mBackground->Update(mScreenSizeX, mScreenSizeY);

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

void GamePlayScene::Draw(shared_ptr<IStepTimer> /*timer*/)
{
	mSpriteRenderer->DrawSprite(mBackground);
}
