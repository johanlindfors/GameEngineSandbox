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

using namespace std;
using namespace Engine;
using namespace Utilities;

GamePlayScene::GamePlayScene(IGameStateCallback* gameCallback)
	: mGame(gameCallback)
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
	mMap->update(timer);
	mPlayer->update(timer);
}

void GamePlayScene::draw(shared_ptr<IRenderer> renderer)
{
	mMap->draw(renderer);
	mPlayer->draw(renderer);
}
