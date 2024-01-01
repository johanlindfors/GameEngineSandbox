#include "PauseScene.hpp"
#include "resources/IResourceManager.hpp"
#include "utilities/IOC.hpp"
#include "scenes/ISceneManager.hpp"
#include "sprites/Sprite.hpp"
#include "renderers/SpriteRenderer.hpp"

using namespace std;
using namespace Engine;
using namespace Engine;

PauseScene::PauseScene()
	: mBackground(make_shared<Sprite>()), mText(make_shared<Sprite>())
{
	id = typeid(PauseScene).name();
}

void PauseScene::load()
{
	auto resourceManager = IOCContainer::instance().resolve<IResourceManager>();

	mBackground->texture = resourceManager->getTexture("pause/background.png");
	mText->texture = resourceManager->getTexture("pause/text.png");
}

void PauseScene::updateScreenSize(int width, int height)
{
	mBackground->size = {
		static_cast<float>(width),
		static_cast<float>(height)};
	mBackground->position = {0.0f, 0.0f};

	mText->size = {
		height / 4.0f,
		width / 4.0f};
	mText->position = {static_cast<float>(width / 2 - mText->size.width / 2),
					   static_cast<float>(height / 2 - mText->size.height / 2)};
}

void PauseScene::draw(shared_ptr<IRenderer> renderer)
{
	auto spriteRenderer = static_pointer_cast<SpriteRenderer>(renderer);
	if (spriteRenderer)
	{
		spriteRenderer->drawSprite(mBackground);
		spriteRenderer->drawSprite(mText);
	}
}