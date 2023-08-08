#include "GamePlayScene.hpp"
#include "resources/IResourceManager.hpp"
#include "utilities/IOC.hpp"
#include "renderers/SpriteRenderer.hpp"
#include "input/IInputManager.hpp"
#include "game/IGameStateCallback.hpp"
#include "utilities/MathHelper.hpp"
#include "game/GameDefines.hpp"
#include "sprites/Sprite.hpp"

#include "components/Components.hpp"
#include <random>

using namespace std;
using namespace Engine;
using namespace Utilities;

GamePlayScene::GamePlayScene(IGameStateCallback* gameCallback)
	: mSpriteSystem(make_unique<sprite_system>())
	, mTransformSystem(make_unique<transform_system>())
	, mMovementSystem(make_unique<movement_system>())
	, mSpawnSystem(make_unique<spawn_system>())
	, mCleanupSystem(make_unique<cleanup_system>())
	, mScoringSystem(make_unique<scoring_system>())
	, mCollisionSystem(make_unique<collision_system>())
	, mScreenSizeX(0)
	, mScreenSizeY(0)
	, mGame(gameCallback)
	, mSpacePressedBefore(false)
{
	id = typeid(GamePlayScene).name();
}

void GamePlayScene::load()
{
	mResourceManager = IOCContainer::instance().resolve<IResourceManager>();
	mInputManager = IOCContainer::instance().resolve<IInputManager>();

	mSpriteSystem->mSprite = make_shared<Engine::Sprite>();

	for(int i = 0; i < 5; i++) {
		spawnApple();
	}

	auto snakeHead = mRegistry.create();
	mRegistry.emplace<position_component>(snakeHead, 10, 10);
	mRegistry.emplace<direction_component>(snakeHead, 0, 1);
	mRegistry.emplace<sprite_component>(snakeHead, mResourceManager->getTexture("snake.png"), 0.0f, 0.0f);
	mRegistry.emplace<input_component>(snakeHead);
	mRegistry.emplace<spawn_component>(snakeHead);

	auto snakeTail = mRegistry.create();
	mRegistry.emplace<position_component>(snakeTail, 10, 10);
	mRegistry.emplace<direction_component>(snakeTail, 0, 0);
	mRegistry.emplace<cleanup_component>(snakeTail, INITIAL_TAIL);
}

void GamePlayScene::spawnApple() 
{
	std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(0, SCREEN_SIZE - 1);

    Point<int> newPosition{0, 0};
	bool collided;
	do {
		collided = false;
		newPosition.x = distr(gen);
		newPosition.y = distr(gen);

		auto objects = mRegistry.view<position_component, static_component>();
		for(const auto& object : objects) {
			const auto& position = objects.get<position_component>(object);
			if(newPosition.x == position.x && newPosition.y == position.y) {
				collided = true;
				break;
			}
		}
	} while (collided);

	auto apple = mRegistry.create();
	mRegistry.emplace<position_component>(apple, newPosition.x, newPosition.y);
	mRegistry.emplace<static_component>(apple);
	mRegistry.emplace<sprite_component>(apple, mResourceManager->getTexture("apple.png"), 0.0f, 0.0f);
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
	mScreenSizeX = width;
	mScreenSizeY = height;

	mSpriteSystem->mScreenWidth = mScreenSizeX;
	mSpriteSystem->mSprite->size = { 
        static_cast<float>(mScreenSizeX / SCREEN_SIZE - 1),
        static_cast<float>(mScreenSizeY / SCREEN_SIZE - 1)
    };
}

void GamePlayScene::update(shared_ptr<IStepTimer> /*timer*/)
{
	auto const spacePressed = mInputManager->isKeyDown(32);
	if (mGame->getCurrentState() == GameState::GamePlay) {

		mMovementSystem->update(mRegistry, mInputManager);
		mSpawnSystem->update(mRegistry, mResourceManager);
		mTransformSystem->update(mRegistry);
		if(mScoringSystem->update(mRegistry)) {
			spawnApple();
			auto entity = mRegistry.view<cleanup_component, direction_component>().front();
			auto& cleanup = mRegistry.get<cleanup_component>(entity);
			cleanup.counter++;
			auto& direction = mRegistry.get<direction_component>(entity);
			direction.x = 0;
			direction.y = 0;
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
