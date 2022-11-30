#include "PauseScene.h"
#include "textures/TextureManager.h"
#include "IOC.hpp"
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
	mBackground->Position = { 0.0f, 0.0f };

	mText->Height = static_cast<int>(height / 4.0f);
	mText->Width = static_cast<int>(width / 4.0f);
	mText->Position = { width / 2.0f - mText->Width / 2.0f, height / 2.0f - mText->Height / 2.0f };
}

void PauseScene::Draw(shared_ptr<ISpriteRenderer> renderer)
{
	if (renderer) {
		renderer->DrawSprite(mBackground);
        renderer->DrawSprite(mText);
	}
}