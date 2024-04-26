#include "GamePlayScene.hpp"

// engine
#include "resources/IResourceManager.hpp"
#include "utilities/IOC.hpp"
#include "renderers/SpriteRenderer.hpp"
#include "input/IInputManager.hpp"
#include "utilities/MathHelper.hpp"
#include "sprites/Sprite.hpp"
#include "utilities/StepTimer.hpp"
#include "audio/IAudioManager.hpp"

// game
#include "game/IGameStateCallback.hpp"
#include "game/GameDefines.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;

GamePlayScene::GamePlayScene(IGameStateCallback *gameCallback)
	: mSpriteSystem(make_unique<SpriteSystem>())
	, mTransformSystem(make_unique<TransformSystem>())
	, mMovementSystem(make_unique<MovementSystem>())
	, mSpawnSystem(make_unique<SpawnSystem>())
	, mCleanupSystem(make_unique<CleanupSystem>())
	, mScoringSystem(make_unique<ScoringSystem>())
	, mCollisionSystem(make_unique<CollisionSystem>())
	, mGame(gameCallback)
	, mSpacePressedBefore(false)
	, mTargetMicroSeconds(1000000 / FRAMES_PER_SECOND)
	, mElapsedMicroSeconds(0)
	, mAudioManager(IOCContainer::resolve_type<IAudioManager>())
{
	id = typeid(GamePlayScene).name();
}

void GamePlayScene::load()
{
	mInputManager = IOCContainer::resolve_type<IInputManager>();

	mSpawnSystem->initialize(mRegistry);
}

void GamePlayScene::unload()
{
	mSpriteSystem.reset();
	mTransformSystem.reset();
	mMovementSystem.reset();
	mSpawnSystem.reset();
	mCleanupSystem.reset();
	mScoringSystem.reset();

	mRegistry.clear();
}

void GamePlayScene::updateScreenSize(int width, int height)
{
	mSpriteSystem->updateScreenSize(width, height);
}

void GamePlayScene::update(shared_ptr<IStepTimer> timer)
{
	auto const spacePressed = mInputManager->isKeyDown(32);
	if (mGame->getCurrentState() == GameState::GamePlay)
	{
		mMovementSystem->update(mRegistry, mInputManager);

		mElapsedMicroSeconds += timer->getDeltaMicroSeconds();
		;
		if (mElapsedMicroSeconds >= mTargetMicroSeconds)
		{
			mElapsedMicroSeconds -= mTargetMicroSeconds;

			mSpawnSystem->update(mRegistry);
			mTransformSystem->update(mRegistry);
			if (mScoringSystem->update(mRegistry))
			{
				mSpawnSystem->spawnApple(mRegistry);
				mCleanupSystem->resetCounter(mRegistry, 1);
				mAudioManager->playSound("score.wav");
			}
			mCleanupSystem->update(mRegistry);
			if (mCollisionSystem->update(mRegistry))
			{
				mGame->goToState(GameState::GameOver);
			}
			mSpriteSystem->update(mRegistry);
		}

		if (spacePressed && !mSpacePressedBefore)
		{
			mGame->goToState(GameState::Pause);
		}
	}
	else
	{
		if (spacePressed && !mSpacePressedBefore)
		{
			mGame->goToState(GameState::GamePlay);
		}
	}
	mSpacePressedBefore = spacePressed;
}

void GamePlayScene::draw(shared_ptr<IRenderer> renderer)
{
	renderer->clear(0.0, 0.0, 0.0, 1.0);
	mSpriteSystem->render(mRegistry, renderer);
}
