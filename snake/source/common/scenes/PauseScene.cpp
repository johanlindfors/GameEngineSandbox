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
	ID = typeid(PauseScene).name();
}

void PauseScene::Load()
{
	auto resourceManager = IOCContainer::Instance().Resolve<IResourceManager>();

	mBackground->Texture = resourceManager->GetTexture("pause/background.png");
    mText->Texture = resourceManager->GetTexture("pause/text.png");
}

void PauseScene::UpdateScreenSize(int width, int height) 
{
	mBackground->Height = height;
	mBackground->Width = width;
	mBackground->Position = { 0, 0 };

	mText->Height = height / 4;
	mText->Width = width / 4;
	mText->Position = { static_cast<float>(width / 2 - mText->Width / 2), 
						static_cast<float>(height / 2 - mText->Height / 2) };
}

void PauseScene::Draw(shared_ptr<IRenderer> renderer)
{
	auto spriteRenderer = static_pointer_cast<ISpriteRenderer>(renderer);
	if (spriteRenderer) {
		spriteRenderer->DrawSprite(mBackground);
        spriteRenderer->DrawSprite(mText);
	}
}