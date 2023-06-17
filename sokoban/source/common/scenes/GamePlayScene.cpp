#include "GamePlayScene.hpp"
#include "resources/IResourceManager.hpp"
#include "utilities/IOC.hpp"
#include "renderers/SpriteRenderer.hpp"
#include "input/IInputManager.hpp"
#include "game/IGameStateCallback.hpp"
#include "game/GameDefines.hpp"
#include "renderers/Sprite.hpp"
#include "objects/Map.hpp"
#include "objects/Player.hpp"
#include "utilities/TweenEngine.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;

GamePlayScene::GamePlayScene(IGameStateCallback* gameCallback)
	: mGame(gameCallback)
	, mInputManager(IOCContainer::instance().resolve<IInputManager>())
	, mTweenEngine(IOCContainer::instance().resolve<ITweenEngine>())
	, mMap(IOCContainer::instance().resolve<Map>())
	, mPlayer(make_unique<Player>())
	, mCratePushes(0)
	, mPlayerMoves(0)
{
	id = typeid(GamePlayScene).name();
}

GamePlayScene::~GamePlayScene()
{
    mMap.reset();
	mPlayer.reset();
}

void GamePlayScene::load()
{
	printf("[GamePlayScene::load]\n");
	auto resourceManager = IOCContainer::instance().resolve<IResourceManager>();
	mInputManager = IOCContainer::instance().resolve<IInputManager>();

	mPlayer->initialize(mMap->playerStartPosition.x, mMap->playerStartPosition.y);
}

void GamePlayScene::unload()
{

}

void GamePlayScene::updateScreenSize(int width, int height)
{
	// mScreenSizeX = width;
	// mScreenSizeY = height;
}

void GamePlayScene::update(shared_ptr<IStepTimer> timer)
{
	handleInput();
	mMap->update(timer);
	mPlayer->update(timer);
	mTweenEngine->update(timer);
}

void GamePlayScene::draw(shared_ptr<IRenderer> renderer)
{
	mMap->draw(renderer);
	mPlayer->draw(renderer);
}

void GamePlayScene::move(int deltaX, int deltaY) 
{
	if(mMap->isCrate(mPlayer->posX + deltaX, mPlayer->posY + deltaY)){
		if(mMap->isWalkable(mPlayer->posX + 2 * deltaX, mPlayer->posY + 2 * deltaY)) {
			mMap->moveCrate(deltaX, deltaY, mPlayer->posX, mPlayer->posY, [&]() {
				if(mMap->checkWin()) {
					mGame->goToState(GameState::GameOver);
				}
			});
			movePlayer(deltaX, deltaY);
			mCratePushes++;
		}
	}
	else if(mMap->isWalkable(mPlayer->posX + deltaX, mPlayer->posY + deltaY)){
		movePlayer(deltaX, deltaY);
	}
}

void GamePlayScene::updateStatus()  {
    printf("%d / %d\n", mPlayerMoves, mCratePushes);
}

void GamePlayScene::movePlayer(int deltaX, int deltaY)
{
	mPlayer->move(deltaX, deltaY);
	mPlayerMoves++;
	updateStatus();
}


void GamePlayScene::handleInput()
{
	if(mPlayer->isMoving) {
		return;
	}
	if (mInputManager->isKeyDown(37)) {
		move(-1, 0);
	}
	if (mInputManager->isKeyDown(39)) {
		move(1, 0);
	}
	if (mInputManager->isKeyDown(40)) {
		move(0, -1);
	}
	if (mInputManager->isKeyDown(38)) {
		move(0, 1);
	}
}