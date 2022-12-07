#include "GamePlayScene.h"
#include "textures/TextureManager.h"
#include "utilities/IOC.hpp"
#include "objects/Bird.h"
#include "physics/IObjectCollider.h"
#include "textures/ITextureManager.h"
#include "renderer/ISpriteRenderer.h"
#include "physics/IPhysicsEngine.h"
#include "utilities/TweenEngine.h"
#include "input/IInputManager.h"
#include "game/IGameStateCallback.h"
#include "utilities/MathHelper.h"
#include "game/GameDefines.h"
#include "renderer/Sprite.h"
#include "objects/ParallaxBackground.h"
#include "utilities/IStepTimer.h"
#include "objects/Pipes.h"
#include <cstdlib> 
#include <ctime> 

using namespace std;
using namespace Engine;
using namespace Utilities;

GamePlayScene::GamePlayScene(IGameStateCallback* gameCallback)
	: mBackground(make_shared<Sprite>())
	, mSkyline(make_unique<ParallaxBackground>())
	, mBird(make_shared<Bird>(Point<float>(80,250)))
	, mPipes(vector<shared_ptr<Pipes>>())
	, mInputManager(IOCContainer::Instance().Resolve<IInputManager>())
	, mPhysicsEngine(IOCContainer::Instance().Resolve<IPhysicsEngine>())
	, mCollider(IOCContainer::Instance().Resolve<IObjectCollider>())
	, mTweenEngine(IOCContainer::Instance().Resolve<ITweenEngine>())
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

void GamePlayScene::Reset()
{
	for (auto pipe : mPipes)
	{
		pipe.reset();
	}
	
	mPipes.clear();
	mBird->Reset();
	mPipesGenerator.Reset();
	mSkyline->Resume();
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
		newPipes = make_shared<Pipes>(Point<float>(288 + 45, 0));
		mPipes.push_back(newPipes);
	}
	auto y = rand()%200 - 100;
	newPipes->Reset(Point<float>(288 + 45, y));
}

void GamePlayScene::Update(shared_ptr<IStepTimer> timer)
{
	auto const spacePressed = mInputManager->IsKeyDown(32);
	if (mGame->GetCurrentState() == GameState::GamePlay) {
		mSkyline->Update(timer);
		// do updates
		mBird->Update(timer);
		mPhysicsEngine->Update(timer);
		
		bool collision = false;
		for(auto pipe : mPipes) {
			collision = mCollider->Intersects(mBird->Bounds, pipe->TopPipe->AABB) || 
						mCollider->Intersects(mBird->Bounds, pipe->BottomPipe->AABB);
			if(collision && mBird->IsAlive) { // Collided with a pipe
				mBird->CollideWithPipe();
				mPipesGenerator.Pause();
				mSkyline->Pause();
			}

			collision = mCollider->Intersects(mBird->Bounds, mSkyline->GetGroundAABB());
			if(collision) {
				mPipesGenerator.Pause();
				mSkyline->Pause();
				mBird->AllowGravity = false;
				mGame->GoToState(GameState::GameOver);
			}
		}
		if(!mBird->IsKilled) {
			for(auto pipe : mPipes) {
				pipe->Update(timer);
			}
		}

		mPipesGenerator.Update([&]()
		{
			GeneratePipes();
		});

		mTweenEngine->Update(timer);

		if (spacePressed && !mSpacePressedBefore)
		{
			mBird->Flap();
		}
	}
	else {
		if (spacePressed && !mSpacePressedBefore)
		{
			Reset();
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
