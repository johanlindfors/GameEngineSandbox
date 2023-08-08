#include "GamePlayScene.hpp"
#include "resources/IResourceManager.hpp"
#include "utilities/IOC.hpp"
#include "objects/Snake.hpp"
#include "objects/Apple.hpp"
#include "objects/PointCollider.hpp"
#include "renderers/SpriteRenderer.hpp"
#include "input/IInputManager.hpp"
#include "game/IGameStateCallback.hpp"
#include "utilities/MathHelper.hpp"
#include "game/GameDefines.hpp"
#include "sprites/Sprite.hpp"

#include "components/Components.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;

GamePlayScene::GamePlayScene(IGameStateCallback* gameCallback)
	: mSpriteSystem(make_unique<sprite_system>())
	, mTransformSystem(make_unique<transform_system>())
	, mMovementSystem(make_unique<movement_system>())
	// , mApple(make_shared<Apple>(Point<int>{SCREEN_SIZE / 4, SCREEN_SIZE / 4}))
	// , mSnake(make_shared<Snake>(Point<int>{SCREEN_SIZE / 2, SCREEN_SIZE / 2}))
	, mCollider(make_shared<PointCollider>())
	, mScreenSizeX(0)
	, mScreenSizeY(0)
	, mGame(gameCallback)
	, mSpacePressedBefore(false)
{
	id = typeid(GamePlayScene).name();
}

void GamePlayScene::load()
{
	auto resourceManager = IOCContainer::instance().resolve<IResourceManager>();
	mInputManager = IOCContainer::instance().resolve<IInputManager>();

	// mApple->setTexture(resourceManager->getTexture("apple.png"));
	// mSnake->setTexture(resourceManager->getTexture("snake.png"));

	mSpriteSystem->mSprite = make_shared<Engine::Sprite>();

	auto apple = mRegistry.create();
	mRegistry.emplace<position_component>(apple, 4, 4);
	mRegistry.emplace<sprite_component>(apple, resourceManager->getTexture("apple.png"), 0.0f, 0.0f);

	auto snakeHead = mRegistry.create();
	mRegistry.emplace<position_component>(snakeHead, 10, 10);
	mRegistry.emplace<direction_component>(snakeHead, 0, 1);
	mRegistry.emplace<input_component>(snakeHead);
	mRegistry.emplace<sprite_component>(snakeHead, resourceManager->getTexture("snake.png"), 0.0f, 0.0f);

	auto snakeTail = mRegistry.create();
	mRegistry.emplace<position_component>(snakeTail, 10, 10);
	mRegistry.emplace<direction_component>(snakeTail, 0, 1);
}

void GamePlayScene::unload()
{
	mApple.reset();
	mSnake.reset();
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
		mTransformSystem->update(mRegistry);
		mSpriteSystem->update(mRegistry);

		// mSnake->handleInput(mInputManager);

		// do updates
		// mApple->update(mScreenSizeX, mScreenSizeY);
		// mSnake->update(mScreenSizeX, mScreenSizeY, mGame);

		// auto headPosition = mSnake->getHeadPosition();
		// if (mCollider->collides(
		// 	Point<int>{static_cast<int>(headPosition.x),
		// 			   static_cast<int>(headPosition.y)}, 
		// 	Point<int>{static_cast<int>(mApple->getSprite()->position.x),
		//     		   static_cast<int>(mApple->getSprite()->position.y)}
		// ))
		// {
		// 	mApple->reset(mSnake, mCollider);
		// 	mSnake->increaseLength();
		// }

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
	// auto spriteRenderer = static_pointer_cast<SpriteRenderer>(renderer);
	// if(spriteRenderer) {
		mSpriteSystem->render(mRegistry, renderer);

		// mApple->draw(spriteRenderer);
		// mSnake->draw(spriteRenderer);
	// }
}
