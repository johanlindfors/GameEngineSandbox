#include "GamePlayScene.hpp"

// engine
#include "utilities/IOC.hpp"
#include "utilities/TweenEngine.hpp"
#include "renderers/SpriteRenderer.hpp"
#include "renderers/FontRenderer.hpp"
#include "input/IInputManager.hpp"

// game
#include "game/IGameStateCallback.hpp"
#include "game/GameDefines.hpp"
#include "objects/Map.hpp"
#include "objects/Player.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;

GamePlayScene::GamePlayScene(IGameStateCallback* gameCallback)
	: mGame(gameCallback)
	, mInputManager(IOCContainer::resolve_type<IInputManager>())
	, mTweenEngine(IOCContainer::resolve_type<ITweenEngine>())
	, mFontRenderer(IOCContainer::resolve_type<FontRenderer>())
	, mMap(IOCContainer::resolve_type<Map>())
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
	mInputManager = IOCContainer::instance().resolve<IInputManager>();

	mPlayer->initialize(mMap->playerStartPosition.x, mMap->playerStartPosition.y);
}

void GamePlayScene::unload()
{
	printf("[GamePlayScene::unload]\n");
}

void GamePlayScene::updateScreenSize(int width, int height)
{
	// mScreenSizeX = width;
	// mScreenSizeY = height;
}

void GamePlayScene::update(shared_ptr<IStepTimer> timer)
{
	handleInput();
	mPlayer->update(timer);
	mTweenEngine->update(timer);
}

void GamePlayScene::draw(shared_ptr<IRenderer> renderer)
{
	mMap->draw(renderer);
	mPlayer->draw(renderer);
	mFontRenderer->drawString(to_string(mPlayerMoves), { 16, 400 - 24 }, 1.0f);
	mFontRenderer->drawString(to_string(mCratePushes), { 400 - 16, 400 - 24 }, 1.0f);
}

void GamePlayScene::move(int deltaX, int deltaY) 
{
	if(mMap->isWalkable(mPlayer->posX + deltaX, mPlayer->posY + deltaY)) {
		movePlayer(deltaX, deltaY);
	}
	else if(mMap->isCrate(mPlayer->posX + deltaX, mPlayer->posY + deltaY)) {
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
}

void GamePlayScene::movePlayer(int deltaX, int deltaY)
{
	mPlayer->move(deltaX, deltaY);
	mPlayer->posX += deltaX;
	mPlayer->posY += deltaY;
	mPlayerMoves++;
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
