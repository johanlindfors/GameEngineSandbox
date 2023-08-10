#include "GamePlayScene.hpp"

// engine
#include "resources/IResourceManager.hpp"
#include "utilities/IOC.hpp"
#include "renderers/SpriteRenderer.hpp"
#include "input/IInputManager.hpp"
#include "utilities/MathHelper.hpp"
#include "sprites/Sprite.hpp"

// game
#include "game/IGameStateCallback.hpp"
#include "game/GameDefines.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;

GamePlayScene::GamePlayScene(IGameStateCallback* gameCallback)
	: mSpriteSystem(make_unique<SpriteSystem>())
	, mTransformSystem(make_unique<TransformSystem>())
	, mMovementSystem(make_unique<MovementSystem>())
	, mSpawnSystem(make_unique<SpawnSystem>())
	, mCleanupSystem(make_unique<CleanupSystem>())
	, mScoringSystem(make_unique<ScoringSystem>())
	, mCollisionSystem(make_unique<CollisionSystem>())
	, mGame(gameCallback)
	, mSpacePressedBefore(false)
{
	id = typeid(GamePlayScene).name();
}

void GamePlayScene::load()
{
	mInputManager = IOCContainer::instance().resolve<IInputManager>();

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

void GamePlayScene::update(shared_ptr<IStepTimer> /*timer*/)
{
	auto const spacePressed = mInputManager->isKeyDown(32);
	if (mGame->getCurrentState() == GameState::GamePlay) {

		mMovementSystem->update(mRegistry, mInputManager);
		mSpawnSystem->update(mRegistry);
		mTransformSystem->update(mRegistry);
		if(mScoringSystem->update(mRegistry)) {
			mSpawnSystem->spawnApple(mRegistry);
			mCleanupSystem->resetCounter(mRegistry, 1);
		}
		mCleanupSystem->update(mRegistry);
		if(mCollisionSystem->update(mRegistry)) {
			mGame->goToState(GameState::GameOver);
		}
		mSpriteSystem->update(mRegistry);

		if (spacePressed && !mSpacePressedBefore)
		{
			mGame->goToState(GameState::Pause);
		}
	}
	else {
		if (spacePressed && !mSpacePressedBefore)
		{
			mGame->goToState(GameState::GamePlay);
		}
	}
	mSpacePressedBefore = spacePressed;
}

void GamePlayScene::draw(shared_ptr<IRenderer> renderer)
{
	mSpriteSystem->render(mRegistry, renderer);
}
