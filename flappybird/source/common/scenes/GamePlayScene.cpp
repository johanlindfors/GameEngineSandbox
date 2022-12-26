#include "GamePlayScene.h"
#include "utilities/IOC.hpp"
#include "objects/Bird.h"
#include "physics/IObjectCollider.h"
#include "renderers/ISpriteRenderer.h"
#include "physics/IPhysicsEngine.h"
#include "utilities/TweenEngine.h"
#include "input/IInputManager.h"
#include "game/IGameStateCallback.h"
#include "utilities/MathHelper.h"
#include "game/GameDefines.h"
#include "renderers/Sprite.h"
#include "objects/ParallaxBackground.h"
#include "utilities/IStepTimer.h"
#include "objects/Pipes.h"
#include "objects/Ground.h"
#include "renderers/FontRenderer.h"
#include <cstdlib> 
#include <ctime>
#include <string>

using namespace std;
using namespace Engine;
using namespace Utilities;

GamePlayScene::GamePlayScene(IGameStateCallback* gameCallback)
	: mBackground(make_shared<Sprite>())
	, mSkyline(make_unique<ParallaxBackground>())
	, mBird(make_shared<Bird>(Point<float>(100,240)))
	, mGround(make_shared<Ground>(Point<float>(0,70), Vector2(SCROLL_SPEED,0)))
	, mPipes(vector<shared_ptr<Pipes>>())
	, mInputManager(IOCContainer::Instance().Resolve<IInputManager>())
	, mPhysicsEngine(IOCContainer::Instance().Resolve<IPhysicsEngine>())
	, mCollider(IOCContainer::Instance().Resolve<IObjectCollider>())
	, mTweenEngine(IOCContainer::Instance().Resolve<ITweenEngine>())
	, mScreenSizeX(0)
	, mScreenSizeY(0)
	, mGame(gameCallback)
	, mSpacePressedBefore(true)
	, mFontRenderer(IOCContainer::Instance().Resolve<FontRenderer>())
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
	mGround.reset();
}

void GamePlayScene::UpdateScreenSize(int width, int height)
{
	mScreenSizeX = width;
	mScreenSizeY = height;

	mFontRenderer->UpdateWindowSize(width, height);
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
	mGround->Resume();
	mScore = 0;
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
		mGround->Update(timer);

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
				mGround->Pause();
			}
			if(!pipe->HasScored && pipe->BottomPipe->Position.X < mBird->Position.X) {
				mScore++;
				pipe->HasScored = true;
			}
		}
		collision = mCollider->Intersects(mBird->Bounds, mGround->AABB);
		if(collision) {
			mPipesGenerator.Pause();
			mSkyline->Pause();
			mBird->AllowGravity = false;
			mGame->GoToState(GameState::GameOver);
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
	mGround->Draw(renderer);
	mFontRenderer->DrawString(to_string(mScore), Point<float>(mScreenSizeX/2,mScreenSizeY/2+200));
}
