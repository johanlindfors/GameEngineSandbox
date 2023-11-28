#include "GamePlayScene.hpp"
#include "utilities/IOC.hpp"
#include "objects/Bird.hpp"
#include "physics/IObjectCollider.hpp"
#include "renderers/SpriteRenderer.hpp"
#include "physics/IPhysicsEngine.hpp"
#include "utilities/TweenEngine.hpp"
#include "input/IInputManager.hpp"
#include "game/IGameStateCallback.hpp"
#include "utilities/MathHelper.hpp"
#include "game/GameDefines.hpp"
#include "sprites/Sprite.hpp"
#include "objects/ParallaxBackground.hpp"
#include "utilities/IStepTimer.hpp"
#include "objects/Pipes.hpp"
#include "objects/Ground.hpp"
#include "renderers/FontRenderer.hpp"
#include "systems/ScoreSystem.hpp"
#include <cstdlib>
#include <ctime>
#include <string>
#include "resources/IResourceManager.hpp"
#include "utilities/Logger.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;

GamePlayScene::GamePlayScene(IGameStateCallback *gameCallback)
	: mBackground(make_shared<Sprite>()), 
	  mSkyline(make_unique<ParallaxBackground>()), 
	  mBird(make_shared<Bird>(Point<float>{80, SCREEN_HEIGHT / 2.0f})), 
	  mGround(make_shared<Ground>(Point<float>{0, 79}, Vector2{SCROLL_SPEED, 0})), 
	  mPipes(vector<shared_ptr<Pipes>>()), 
	  mInputManager(IOCContainer::instance().resolve<IInputManager>()), 
	  mPhysicsEngine(IOCContainer::instance().resolve<IPhysicsEngine>()), 
	  mCollider(IOCContainer::instance().resolve<IObjectCollider>()), 
	  mTweenEngine(IOCContainer::instance().resolve<ITweenEngine>()), 
	  mScreenSizeX(0), mScreenSizeY(0), mGame(gameCallback), mSpacePressedBefore(true), 
	  //mFontRenderer(IOCContainer::instance().resolve<FontRenderer>()), 
	  mShowInstructions(true), mScore(0)
{
	id = typeid(GamePlayScene).name();
	mPipesGenerator.setInterval(1250000);

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
	debuglog << "[GamePlayScene::load]" << endl;

	auto resourceManager = IOCContainer::instance().resolve<IResourceManager>();
	auto atlas = resourceManager->getTexture("atlas.png");
	mBackground->texture.textureIndex = atlas.textureIndex;

	// mBackground->offset = 3;
	mBackground->size = {288.0f, 505.0f};
	mBackground->offset = {
		40.0f / 512.0f, (512.0f - 72.0f) / 512.0f,
		4.0f / 512.0f, 4.0f / 512.0f};
	mSkyline->initializeSprites();
	mGround->initializeSprite();

	mBird->initializeSprite();
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

	//mFontRenderer->updateWindowSize(width, height);
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
		if (!pipe->isAlive)
		{
			newPipes = pipe;
			break;
		}
	}
	if (newPipes == nullptr)
	{
		newPipes = make_shared<Pipes>(Point<float>{288 + 45, 0});
		mPipes.push_back(newPipes);
	}
	auto y = mDistrib(mGen) - 100;
	newPipes->reset(Point<float>{
		static_cast<float>(288 + 45),
		static_cast<float>(y)});
}

void GamePlayScene::update(shared_ptr<IStepTimer> timer)
{
	auto const mousePressed = mInputManager->getMouseState().state == ButtonState::Pressed;
	auto const spacePressed = mInputManager->isKeyDown(32);

	switch (mGame->getCurrentState())
	{
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

		if (!mBird->isKilled)
		{
			for (auto pipe : mPipes)
			{
				pipe->update(timer);
			}
		}

		mPipesGenerator.update([&]()
							   { generatePipes(); });

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
	for (auto pipe : mPipes)
	{
		bool collision = mCollider->intersects(mBird->bounds, pipe->topPipe->AABB) ||
						 mCollider->intersects(mBird->bounds, pipe->bottomPipe->AABB);
		if (collision && mBird->isAlive)
		{ // Collided with a pipe
			mBird->collideWithPipe();
			mPipesGenerator.pause();
			mSkyline->pause();
			mGround->pause();
		}
		if (!pipe->hasScored && pipe->bottomPipe->position.x < mBird->position.x)
		{
			mScore++;
			pipe->hasScored = true;
		}
	}

	if (mCollider->intersects(mBird->bounds, mGround->AABB))
	{
		auto scoreSystem = IOCContainer::instance().resolve<ScoreSystem>();
		scoreSystem->setLatestScore(mScore);
		mPipesGenerator.pause();
		mSkyline->pause();
		mGround->pause();
		mBird->collideWithPipe();
		mBird->allowGravity = false;
		mGame->goToState(GameState::GameOver);
	}
}

void GamePlayScene::draw(shared_ptr<IRenderer> renderer)
{
	auto spriteRenderer = static_pointer_cast<SpriteRenderer>(renderer);
	if (spriteRenderer)
		spriteRenderer->drawSprite(mBackground);
	mSkyline->draw(renderer);
	mBird->draw(renderer);
	for (auto pipe : mPipes)
		pipe->draw(renderer);
	mGround->draw(renderer);
	if (mGame->getCurrentState() == GameState::GamePlay)
	{
		float x = mScreenSizeX / 2.0f;
		float y = mScreenSizeY / 2.0f + 220.0f;
		//mFontRenderer->drawString(to_string(mScore), FontRenderer::Alignment::Center, Point<float>{x, y}, 0.4f);
	}
}
