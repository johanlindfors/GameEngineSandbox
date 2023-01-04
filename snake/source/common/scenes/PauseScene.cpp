#include "PauseScene.h"
#include "resources/IResourceManager.h"
#include "utilities/IOC.hpp"
#include "scenes/ISceneManager.h"
#include "renderers/Sprite.h"
#include "renderers/ISpriteRenderer.h"

using namespace std;
using namespace Engine;
using namespace Utilities;

PauseScene::PauseScene()
	: mBackground(make_shared<Sprite>())
    , mText(make_shared<Sprite>())
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
	mBackground->height = height;
	mBackground->width = width;
	mBackground->position = { 0, 0 };

	mText->height = height / 4;
	mText->width = width / 4;
	mText->position = { static_cast<float>(width / 2 - mText->width / 2), 
						static_cast<float>(height / 2 - mText->height / 2) };
}

void PauseScene::draw(shared_ptr<IRenderer> renderer)
{
	auto spriteRenderer = static_pointer_cast<ISpriteRenderer>(renderer);
	if (spriteRenderer) {
		spriteRenderer->drawSprite(mBackground);
        spriteRenderer->drawSprite(mText);
	}
}