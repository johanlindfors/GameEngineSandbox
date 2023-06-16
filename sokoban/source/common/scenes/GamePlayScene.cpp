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

void GamePlayScene::handleInput()
{
	if(mPlayer->isMoving) {
		return;
	}
	if (mInputManager->isKeyDown(37)) {
		mPlayer->move(-1, 0);
	}
	if (mInputManager->isKeyDown(39)) {
		mPlayer->move(1, 0);
	}
	if (mInputManager->isKeyDown(40)) {
		mPlayer->move(0, -1);
	}
	if (mInputManager->isKeyDown(38)) {
		mPlayer->move(0, 1);
	}
}
