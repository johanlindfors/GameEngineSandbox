#include "GameOverScene.hpp"
#include "resources/ResourceManager.hpp"
#include "scenes/ISceneManager.hpp"
#include "input/IInputManager.hpp"
#include "renderers/SpriteRenderer.hpp"
#include "sprites/Sprite.hpp"
#include "utilities/IOC.hpp"
#include "game/IGameStateCallback.hpp"

using namespace std;
using namespace Engine;
using namespace Engine;

GameOverScene::GameOverScene(IGameStateCallback *gameCallback)
	: mBackground(make_shared<Sprite>()), mText(make_shared<Sprite>()), mGame(gameCallback)
{
	id = typeid(GameOverScene).name();
}

GameOverScene::~GameOverScene() {}

void GameOverScene::load()
{
	auto resourceManager = IOCContainer::instance().resolve<IResourceManager>();
	mInputManager = IOCContainer::instance().resolve<IInputManager>();

	mBackground->texture = resourceManager->getTexture("gameover/background.png");
	mText->texture = resourceManager->getTexture("gameover/text.png");
}

void GameOverScene::unload() {}

void GameOverScene::updateScreenSize(int width, int height)
{
	mBackground->size = {
		static_cast<float>(width),
		static_cast<float>(height)};
	mBackground->position = {0.0f, 0.0f};

	mText->size = {
		static_cast<float>(width / 4),
		static_cast<float>(height / 4)};
	mText->position = {static_cast<float>(width / 2 - mText->size.width / 2.0f),
					   static_cast<float>(height / 2 - mText->size.height / 2.0f)};
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
	auto spriteRenderer = static_pointer_cast<SpriteRenderer>(renderer);
	if (spriteRenderer)
	{
		spriteRenderer->drawSprite(mBackground);
		spriteRenderer->drawSprite(mText);
	}
}
