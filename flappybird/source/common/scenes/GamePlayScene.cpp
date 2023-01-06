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
#include "systems/ScoreSystem.h"
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;
using namespace Engine;
using namespace Utilities;

GamePlayScene::GamePlayScene(IGameStateCallback* gameCallback)
	: mBackground(make_shared<Sprite>())
	, mSkyline(make_unique<ParallaxBackground>())
	, mBird(make_shared<Bird>(Point<float>{80,SCREEN_HEIGHT/2.0f}))
	, mGround(make_shared<Ground>(Point<float>{0,79}, Vector2{SCROLL_SPEED,0}))
	, mPipes(vector<shared_ptr<Pipes>>())
	, mInputManager(IOCContainer::instance().resolve<IInputManager>())
	, mPhysicsEngine(IOCContainer::instance().resolve<IPhysicsEngine>())
	, mCollider(IOCContainer::instance().resolve<IObjectCollider>())
	, mTweenEngine(IOCContainer::instance().resolve<ITweenEngine>())
	, mScreenSizeX(0)
	, mScreenSizeY(0)
	, mGame(gameCallback)
	, mSpacePressedBefore(true)
	, mFontRenderer(IOCContainer::instance().resolve<FontRenderer>())
	, mShowInstructions(true)
	, mScore(0)
{
	id = typeid(GamePlayScene).name();
	mPipesGenerator.setInterval(1250);

	std::random_device rd;
    mGen = std::mt19937(rd());
	mDistrib = std::uniform_int_distribution<>(0, 200);
	reset();
}

GamePlayScene::~GamePlayScene()
{
	mBackground.reset();
	mSkyline.reset();
	mBird.reset();
	mGround.reset();
}

void GamePlayScene::load()
{
	mBackground->offset = 3;
	mBackground->width = 288;
	mBackground->height = 505;

	mPhysicsEngine->addBody(mBird);
}

void GamePlayScene::unload()
{
	mBackground.reset();
	mSkyline.reset();
	mGround.reset();
}

void GamePlayScene::updateScreenSize(int width, int height)
{
	mScreenSizeX = width;
	mScreenSizeY = height;

	mFontRenderer->updateWindowSize(width, height);
}

void GamePlayScene::reset()
{
	for (auto pipe : mPipes)
	{
		pipe.reset();
	}

	mPipes.clear();
	mBird->reset();
	mPipesGenerator.reset();
	mPipesGenerator.pause();
	mSkyline->resume();
	mGround->resume();
	mScore = 0;
}

void GamePlayScene::generatePipes()
{
 	shared_ptr<Pipes> newPipes = nullptr;
	for (auto pipe : mPipes)
	{
		if(!pipe->isAlive) {
			newPipes = pipe;
			break;
		}
	}
	if(newPipes == nullptr) {
		newPipes = make_shared<Pipes>(Point<float>{288 + 45, 0});
		mPipes.push_back(newPipes);
	}
	auto y = mDistrib(mGen) - 100;
	newPipes->reset(Point<float>{
		static_cast<float>(288 + 45),
		static_cast<float>(y)}
	);
}

void GamePlayScene::update(shared_ptr<IStepTimer> timer)
{
	auto const mousePressed = mInputManager->getMouseState().state == MouseButtonState::Pressed;
	auto const spacePressed = mInputManager->isKeyDown(32);

	switch(mGame->getCurrentState()) {
	case GameState::Instructions:
		reset();
		mSkyline->update(timer);
		mGround->update(timer);
		mBird->update(timer);		
		if (mousePressed || (spacePressed && !mSpacePressedBefore))
		{
			reset();
			mGame->goToState(GameState::GamePlay);
			mPipesGenerator.resume();
		}
		break;
	default:
		// do updates
		mSkyline->update(timer);
		mGround->update(timer);
		mBird->update(timer);
		mPhysicsEngine->update(timer);

		if(!mBird->isKilled) {
			for(auto pipe : mPipes) {
				pipe->update(timer);
			}
		}

		mPipesGenerator.update([&]()
		{
			generatePipes();
		});

		mTweenEngine->update(timer);

		checkCollisions();

		break;
	}

	if (mousePressed || (spacePressed && !mSpacePressedBefore)) 
	{
		mBird->flap();
	}

	mSpacePressedBefore = spacePressed;
}

void GamePlayScene::checkCollisions()
{
	for(auto pipe : mPipes) {
		bool collision = mCollider->intersects(mBird->bounds, pipe->topPipe->AABB) || 
					mCollider->intersects(mBird->bounds, pipe->bottomPipe->AABB);
		if(collision && mBird->isAlive) { // Collided with a pipe
			mBird->collideWithPipe();
			mPipesGenerator.pause();
			mSkyline->pause();
			mGround->pause();
		}
		if(!pipe->hasScored && pipe->bottomPipe->position.x < mBird->position.x) {
			mScore++;
			pipe->hasScored = true;
		}
	}

	if(mCollider->intersects(mBird->bounds, mGround->AABB)) {
		auto scoreSystem= IOCContainer::instance().resolve<ScoreSystem>();
		scoreSystem->setLatestScore(mScore);
		mPipesGenerator.pause();
		mSkyline->pause();
		mBird->allowGravity = false;
		mGame->goToState(GameState::GameOver);
	}
}

void GamePlayScene::draw(shared_ptr<IRenderer> renderer)
{
	auto spriteRenderer = static_pointer_cast<ISpriteRenderer>(renderer);
	spriteRenderer->drawSprite(mBackground);
	mSkyline->draw(spriteRenderer);
	mBird->draw(spriteRenderer); 
	for(auto pipe : mPipes)
		pipe->draw(spriteRenderer);
	mGround->draw(spriteRenderer);
	if(mGame->getCurrentState() == GameState::GamePlay) {
		float x = mScreenSizeX / 2.0f;
		float y = mScreenSizeY / 2.0f + 220.0f;
		mFontRenderer->drawString(to_string(mScore), Point<float>{x,y}, 0.4f);
	}
}
