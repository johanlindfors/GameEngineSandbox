#include "GamePlayScene.hpp"
#include "resources/IResourceManager.hpp"
#include "utilities/IOC.hpp"
#include "renderers/SpriteRenderer.hpp"
#include "input/IInputManager.hpp"
#include "game/IGameStateCallback.hpp"
#include "game/GameDefines.hpp"
#include "renderers/Sprite.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;

GamePlayScene::GamePlayScene(IGameStateCallback* gameCallback)
	: mGame(gameCallback)
{
	id = typeid(GamePlayScene).name();
}

GamePlayScene::~GamePlayScene()
{
    
}

void GamePlayScene::load()
{
	auto resourceManager = IOCContainer::instance().resolve<IResourceManager>();
	mInputManager = IOCContainer::instance().resolve<IInputManager>();

	// mApple->setTexture(resourceManager->getTexture("apple.png"));
	// mSnake->setTexture(resourceManager->getTexture("snake.png"));
}

void GamePlayScene::unload()
{

}

void GamePlayScene::updateScreenSize(int width, int height)
{
	// mScreenSizeX = width;
	// mScreenSizeY = height;
}

void GamePlayScene::update(shared_ptr<IStepTimer> /*timer*/)
{

}

void GamePlayScene::draw(shared_ptr<IRenderer> renderer)
{
	auto spriteRenderer = static_pointer_cast<SpriteRenderer>(renderer);
	if(spriteRenderer) {

	}
}
