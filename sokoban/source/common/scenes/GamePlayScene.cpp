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
{
	id = typeid(GamePlayScene).name();
	mMap = make_unique<Map>();
	mPlayer = make_unique<Player>();
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

	mMap->initialize();
	mPlayer->initialize(mMap->playerStartPosition.x, mMap->playerStartPosition.y);
	// mApple->setTexture(resourceManager->getTexture("apple.png"));
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
			mMap->moveCrate(deltaX, deltaY, mPlayer->posX, mPlayer->posY);
			movePlayer(deltaX, deltaY);
			// this.cratePushes++;
		}
	}
	else if(mMap->isWalkable(mPlayer->posX + deltaX, mPlayer->posY + deltaY)){
		movePlayer(deltaX, deltaY);
	}
}

        // updateStatus()  {
        //     this.status.text = this.map.id + " : " + this.playerMoves + " / " + this.cratePushes;
        // }

void GamePlayScene::movePlayer(int deltaX, int deltaY)
{
	mPlayer->move(deltaX, deltaY);
	// this.playerMoves++
	// this.updateStatus();
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
