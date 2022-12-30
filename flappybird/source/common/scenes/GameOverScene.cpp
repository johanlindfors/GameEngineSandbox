#include "GameOverScene.h"
#include "scenes/ISceneManager.h"
#include "input/IInputManager.h"
#include "renderers/ISpriteRenderer.h"
#include "renderers/Sprite.h"
#include "utilities/IOC.hpp"
#include "game/IGameStateCallback.h"
#include "utilities/ITweenEngine.h"
#include "renderers/FontRenderer.h"
#include "systems/ScoreSystem.h"

using namespace std;
using namespace Engine;
using namespace Utilities;

GameOverScene::GameOverScene(IGameStateCallback* gameCallback)
	: mGameOverText(make_shared<Sprite>())	
	, mScoreBoard(make_shared<Sprite>())
	, mMedal(make_shared<Sprite>())
	, mButton(make_shared<Sprite>())
	, mGame(gameCallback)
	, mInputManager(IOCContainer::Instance().Resolve<IInputManager>())
	, mTweenEngine(IOCContainer::Instance().Resolve<ITweenEngine>())
	, mFontRenderer(IOCContainer::Instance().Resolve<FontRenderer>())
	, mScoreSystem(IOCContainer::Instance().Resolve<ScoreSystem>())
{
	ID = typeid(GameOverScene).name();
}

GameOverScene::~GameOverScene() { 
	mTweenEngine->Clear();
}

void GameOverScene::Load()
{
	mGameOverText->Offset = 7;
	mGameOverText->Width = 48;
	mGameOverText->Height = 12;

	mButton->Offset = 12;
	mButton->Width = 104;
	mButton->Height = 58;
	mButton->Position = Point<float>(92,176);

	mScoreBoard->Offset = 11;
	mScoreBoard->Width = 225;
	mScoreBoard->Height = 113;
	mScoreBoard->Position = Point<float>(144.0f - mScoreBoard->Width/2, 250.0);

	mMedal->Offset = 9; // Silver
	mMedal->Width = 44;
	mMedal->Height = 44;
	mMedal->Position = mScoreBoard->Position + Point<float>(25.0, 25.0);

	mTweenEngine->Add(mGameOverText->Width,[&](float value)
	{ 
		mGameOverText->Width = value; 
	}, 192, 1000, true);
	mTweenEngine->Add(mGameOverText->Height,[&](float value)
	{ 
		mGameOverText->Height = value;
	}, 48, 1000, true);
}

void GameOverScene::Unload() { }

void GameOverScene::UpdateScreenSize(int width, int height) { }

void GameOverScene::HandleInput() { }

void GameOverScene::Update(shared_ptr<IStepTimer> timer)
{
	mTweenEngine->Update(timer);
	mGameOverText->Position = { 288.0f / 2.0f - mGameOverText->Width / 2.0f, 
								505.0f / 2.0f - mGameOverText->Height / 2.0f + 150.0f };
	HandleInput();
}

void GameOverScene::Draw(shared_ptr<IRenderer> renderer)
{
	auto spriteRenderer = static_pointer_cast<ISpriteRenderer>(renderer);
	auto score = mScoreSystem->GetLatestScore();
	if (spriteRenderer) {
		spriteRenderer->DrawSprite(mGameOverText);
		spriteRenderer->DrawSprite(mButton);
		spriteRenderer->DrawSprite(mScoreBoard);
		if(score >= 10) {
			if(score >= 20) {
				mMedal->Offset = 10;
			}
			spriteRenderer->DrawSprite(mMedal);
		}
        mFontRenderer->DrawString(to_string(score), Point<float>(mScoreBoard->Position.X + 200, mScoreBoard->Position.Y + 68), 0.3f);
        mFontRenderer->DrawString(to_string(mScoreSystem->GetHighScore()), Point<float>(mScoreBoard->Position.X + 200, mScoreBoard->Position.Y + 18), 0.3f);
	}
}
