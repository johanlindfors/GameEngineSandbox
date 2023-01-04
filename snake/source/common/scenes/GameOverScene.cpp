#include "GameOverScene.h"
#include "resources/ResourceManager.h"
#include "scenes/ISceneManager.h"
#include "input/IInputManager.h"
#include "renderers/SpriteRenderer.h"
#include "renderers/Sprite.h"
#include "utilities/IOC.hpp"
#include "game/IGameStateCallback.h"

using namespace std;
using namespace Engine;
using namespace Utilities;

GameOverScene::GameOverScene(IGameStateCallback* gameCallback)
	: mBackground(make_shared<Sprite>())	
	, mText(make_shared<Sprite>())
	, mGame(gameCallback)	
{
	id = typeid(GameOverScene).name();
}

GameOverScene::~GameOverScene() { }

void GameOverScene::load()
{
	auto resourceManager = IOCContainer::instance().resolve<IResourceManager>();
	mInputManager = IOCContainer::instance().resolve<IInputManager>();

	mBackground->texture = resourceManager->getTexture("gameover/background.png");
    mText->texture = resourceManager->getTexture("gameover/text.png");
}

void GameOverScene::unload() { }

void GameOverScene::updateScreenSize(int width, int height) 
{
	mBackground->height = height;
	mBackground->width = width;
	mBackground->position = { 0, 0 };

	mText->height = height / 4;
	mText->width = width / 4;
	mText->position = { static_cast<float>(width / 2 - mText->width / 2), 
						static_cast<float>(height / 2 - mText->height / 2) };
}

void GameOverScene::handleInput() 
{
	if (mInputManager->isKeyDown(32)) // SpaceBar
	{
		mGame->goToState(GameState::GamePlay);
	}
}

void GameOverScene::update(shared_ptr<IStepTimer> timer)
{
	handleInput();
}

void GameOverScene::draw(shared_ptr<IRenderer> renderer)
{
	auto spriteRenderer = static_pointer_cast<ISpriteRenderer>(renderer);
	if (spriteRenderer) {
		spriteRenderer->drawSprite(mBackground);
        spriteRenderer->drawSprite(mText);
	}
}
