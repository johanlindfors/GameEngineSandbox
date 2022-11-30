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
#include "IStepTimer.h"

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
	, mBird(make_shared<Bird>(Vector2(132,250)))
	, mPhysicsEngine(make_unique<PhysicsEngine>())
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

	mBackground->Offset = 3;
	mBackground->Width = 288;
	mBackground->Height = 505;

	mPhysicsEngine->AddBody(mBird);
}

void GamePlayScene::Unload()
{
	mBackground.reset();
	mSkyline.reset();
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

		mSkyline->Update(timer);
		// do updates
		mBird->Update(timer);
		mPhysicsEngine->Update(timer);
		// if (mCollider->Collides(mSnake->GetSprite()->Position, mApple->GetSprite()->Position))
		// {

		// }

		if (spacePressed && !mSpacePressedBefore)
		{
			mBird->Flap();
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
	mSkyline->Draw(renderer);
	mBird->Draw(renderer);
}

void PhysicsEngine::AddBody(shared_ptr<IPhysicsBody> body)
{
	mBodies.push_back(body);
}

void PhysicsEngine::Update(shared_ptr<IStepTimer> timer)
{
	for (auto body : mBodies)
	{
		if(!body->IsAlive) continue;
		
		auto velocity = body->Velocity;
		if (body->AllowGravity)
		{
			velocity.m[1] = velocity.m[1] - (GRAVITY * timer->GetElapsedMilliSeconds() / 10);
		}

		body->Y = body->Y + (velocity.m[1] * timer->GetElapsedMilliSeconds() / 1000);
		body->X = body->X + (velocity.m[0] * timer->GetElapsedMilliSeconds() / 1000);
		body->Velocity = velocity;
	}	
}
