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
#include "renderers/Sprite.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;

GamePlayScene::GamePlayScene(IGameStateCallback* gameCallback)
	: mApple(make_shared<Apple>(Point<int>{SCREEN_SIZE / 4, SCREEN_SIZE / 4}))
	, mSnake(make_shared<Snake>(Point<int>{SCREEN_SIZE / 2, SCREEN_SIZE / 2}))
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

	mApple->setTexture(resourceManager->getTexture("apple.png"));
	mSnake->setTexture(resourceManager->getTexture("snake.png"));
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
}

void GamePlayScene::update(shared_ptr<IStepTimer> /*timer*/)
{
	auto const spacePressed = mInputManager->isKeyDown(32);
	if (mGame->getCurrentState() == GameState::GamePlay) {
		mSnake->handleInput(mInputManager);

		// do updates
		mApple->update(mScreenSizeX, mScreenSizeY);
		mSnake->update(mScreenSizeX, mScreenSizeY, mGame);

		if (mCollider->collides(
			Point<int>{static_cast<int>(mSnake->getSprite()->position.x),
					   static_cast<int>(mSnake->getSprite()->position.y)}, 
			Point<int>{static_cast<int>(mApple->getSprite()->position.x),
		    		   static_cast<int>(mApple->getSprite()->position.y)}

		))
		{
			mApple->reset(mSnake, mCollider);
			mSnake->increaseLength();
		}

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
	auto spriteRenderer = static_pointer_cast<SpriteRenderer>(renderer);
	if(spriteRenderer) {
		mApple->draw(spriteRenderer);
		mSnake->draw(spriteRenderer);
	}
}
