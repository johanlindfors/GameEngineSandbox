#include "GamePlayScene.h"
#include "textures/TextureManager.h"
#include "IOC.hpp"
#include "objects/Bird.h"
// #include "objects/VectorCollider.h"
#include "textures/ITextureManager.h"
#include "renderer/ISpriteRenderer.h"
#include "physics/IPhysicsEngine.h"
#include "input/IInputManager.h"
#include "game/IGameStateCallback.h"
#include "MathHelper.h"
#include "game/GameDefines.h"
#include "renderer/Sprite.h"
#include "objects/ParallaxBackground.h"
#include "IStepTimer.h"
#include "objects/Pipes.h"
#include <cstdlib> 
#include <ctime> 

using namespace std;
using Engine::IInputManager;
using Engine::ISpriteRenderer;
using Engine::ITextureManager;
using Engine::IPhysicsEngine;
using Engine::Sprite;
using Utilities::IStepTimer;
using Utilities::IOCContainer;
using Utilities::Vector2;

GamePlayScene::GamePlayScene(IGameStateCallback* gameCallback)
	: mBackground(make_shared<Sprite>())
	, mSkyline(make_unique<ParallaxBackground>())
	, mBird(make_shared<Bird>(Vector2(132,250)))
	, mPipes(vector<shared_ptr<Pipes>>())
	// , mCollider(make_shared<VectorCollider>())
	, mScreenSizeX(0)
	, mScreenSizeY(0)
	, mGame(gameCallback)
	, mSpacePressedBefore(false)
{
	ID = typeid(GamePlayScene).name();
	mPipesGenerator.SetInterval(1250);

	srand((unsigned)time(0));
}

GamePlayScene::~GamePlayScene()
{

}

void GamePlayScene::Load()
{
	mTextureManager = IOCContainer::Instance().Resolve<ITextureManager>();
	mInputManager = IOCContainer::Instance().Resolve<IInputManager>();
	mPhysicsEngine = IOCContainer::Instance().Resolve<IPhysicsEngine>();

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

void GamePlayScene::GeneratePipes()
{
	shared_ptr<Pipes> newPipes = nullptr;
	for (auto pipe : mPipes)
	{
		if(!pipe->IsAlive) {
			newPipes = pipe;
			break;
		}
	}
	if(newPipes == nullptr) {
		newPipes = make_shared<Pipes>(Vector2(0.0f, 0.0f));
		mPipes.push_back(newPipes);
	}
	auto y = (rand()%200) - 100;
	newPipes->Reset(Vector2(288.0f + 45.0f, static_cast<float>(y)));
}

void GamePlayScene::Update(shared_ptr<IStepTimer> timer)
{
	auto const spacePressed = mInputManager->IsKeyDown(32);
	if (mGame->GetCurrentState() == GameState::GamePlay) {
		mSkyline->Update(timer);
		// do updates
		mBird->Update(timer);
		mPhysicsEngine->Update(timer);
		for(auto pipe : mPipes)
			pipe->Update(timer);

		mPipesGenerator.Update([&]()
		{
			GeneratePipes();
		});
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
	for(auto pipe : mPipes)
		pipe->Draw(renderer);
}
