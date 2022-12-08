#include "GameOverScene.h"
#include "textures/TextureManager.h"
#include "scenes/ISceneManager.h"
#include "input/IInputManager.h"
#include "renderer/ISpriteRenderer.h"
#include "renderer/Sprite.h"
#include "utilities/IOC.hpp"
#include "game/IGameStateCallback.h"
#include "utilities/ITweenEngine.h"

using namespace std;
using namespace Engine;
using namespace Utilities;

GameOverScene::GameOverScene(IGameStateCallback* gameCallback)
	: mBackground(make_shared<Sprite>())	
	, mText(make_shared<Sprite>())
	, mGame(gameCallback)
	, mInputManager(IOCContainer::Instance().Resolve<IInputManager>())
	, mTweenEngine(IOCContainer::Instance().Resolve<ITweenEngine>())
{
	ID = typeid(GameOverScene).name();
}

GameOverScene::~GameOverScene() { }

void GameOverScene::Load()
{
	mBackground->Offset = 7;
	mBackground->Width = 48;
	mBackground->Height = 12;
	
	mTweenEngine->Add(mBackground->Width,[&](float value)
	{ 
		mBackground->Width = value; 
	}, 192, 1000, true);
	mTweenEngine->Add(mBackground->Height,[&](float value)
	{ 
		mBackground->Height = value;
	}, 48, 1000, true);
}

void GameOverScene::Unload() { }

void GameOverScene::UpdateScreenSize(int width, int height) 
{
// 	mText->Height = static_cast<int>(height / 4.0f);
// 	mText->Width = static_cast<int>(width / 4.0f);
// 	mText->Position = { width / 2.0f - mText->Width / 2.0f, height / 2.0f - mText->Height / 2.0f };
}

void GameOverScene::HandleInput() 
{
	// if (mInputManager->IsKeyDown(32)) // SpaceBar
	// {
	// 	mGame->GoToState(GameState::GamePlay);
	// }
}

void GameOverScene::Update(shared_ptr<IStepTimer> timer)
{
	mTweenEngine->Update(timer);
	mBackground->Position = { 288.0f / 2.0f - mBackground->Width / 2.0f, 505.0f / 2.0f - mBackground->Height / 2.0f + 100.0f };
	HandleInput();
}

void GameOverScene::Draw(shared_ptr<ISpriteRenderer> renderer)
{
	if (renderer) {
		renderer->DrawSprite(mBackground);
        //renderer->DrawSprite(mText);
	}
}
