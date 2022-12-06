#include "PauseScene.h"
#include "textures/TextureManager.h"
#include "utilities/IOC.hpp"
#include "scenes/ISceneManager.h"
#include "renderer/Sprite.h"
#include "renderer/ISpriteRenderer.h"

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
	mTextureManager = IOCContainer::Instance().Resolve<ITextureManager>();
    
	mBackground->Texture = mTextureManager->GetTexture(L"pause/background.png");
    mText->Texture = mTextureManager->GetTexture(L"pause/text.png");
}

void PauseScene::UpdateScreenSize(int width, int height) 
{
	mBackground->Height = height;
	mBackground->Width = width;
	mBackground->Position = { 0, 0 };

	mText->Height = static_cast<int>(height / 4);
	mText->Width = static_cast<int>(width / 4);
	mText->Position = { width / 2 - mText->Width / 2, height / 2 - mText->Height / 2 };
}

void PauseScene::Draw(shared_ptr<ISpriteRenderer> renderer)
{
	if (renderer) {
		renderer->DrawSprite(mBackground);
        renderer->DrawSprite(mText);
	}
}