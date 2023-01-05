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
	, mInputManager(IOCContainer::instance().resolve<IInputManager>())
	, mTweenEngine(IOCContainer::instance().resolve<ITweenEngine>())
	, mFontRenderer(IOCContainer::instance().resolve<FontRenderer>())
	, mScoreSystem(IOCContainer::instance().resolve<ScoreSystem>())
{
	id = typeid(GameOverScene).name();
}

GameOverScene::~GameOverScene() { 
	mTweenEngine->clear();
}

void GameOverScene::load()
{
	mGameOverText->offset = 7;
	mGameOverText->width = 48;
	mGameOverText->height = 12;

	mButton->offset = 12;
	mButton->width = 104;
	mButton->height = 58;
	mButton->position = Point<float>{92,176};

	mScoreBoard->offset = 11;
	mScoreBoard->width = 225;
	mScoreBoard->height = 113;
	mScoreBoard->position = Point<float>{144.0f - mScoreBoard->width/2, 250.0};

	mMedal->offset = 9; // Silver
	mMedal->width = 44;
	mMedal->height = 44;
	mMedal->position = mScoreBoard->position + Point<float>{25.0, 25.0};

	mTweenEngine->add(mGameOverText->width,[&](float value)
	{ 
		mGameOverText->width = value; 
	}, 192, 1000, true);
	mTweenEngine->add(mGameOverText->height,[&](float value)
	{ 
		mGameOverText->height = value;
	}, 48, 1000, true);
}

void GameOverScene::unload() { }

void GameOverScene::updateScreenSize(int width, int height) { }

void GameOverScene::handleInput() 
{ 
	auto const mouseState = mInputManager->getMouseState();
	if(mouseState.state == MouseButtonState::Pressed) {
		auto position = mouseState.position;
		if(position.x > 92 && 
		   position.x < 92 + 104 &&
		   position.y > 176 &&
		   position.y < 176 + 58)
		{
			mGame->goToState(GameState::Instructions);
	    }
	}
}

void GameOverScene::update(shared_ptr<IStepTimer> timer)
{
	mTweenEngine->update(timer);
	mGameOverText->position = { 288.0f / 2.0f - mGameOverText->width / 2.0f, 
								505.0f / 2.0f - mGameOverText->height / 2.0f + 150.0f };
	handleInput();
}

void GameOverScene::draw(shared_ptr<IRenderer> renderer)
{
	auto spriteRenderer = static_pointer_cast<ISpriteRenderer>(renderer);
	auto score = mScoreSystem->getLatestScore();
	if (spriteRenderer) {
		spriteRenderer->drawSprite(mGameOverText);
		spriteRenderer->drawSprite(mButton);
		spriteRenderer->drawSprite(mScoreBoard);
		if(score >= 10) {
			if(score >= 20) {
				mMedal->offset = 10;
			}
			spriteRenderer->drawSprite(mMedal);
		}
        mFontRenderer->drawString(to_string(score), Point<float>{mScoreBoard->position.x + 200, mScoreBoard->position.y + 68}, 0.3f);
        mFontRenderer->drawString(to_string(mScoreSystem->getHighScore()), Point<float>{mScoreBoard->position.x + 200, mScoreBoard->position.y + 18}, 0.3f);
	}
}
