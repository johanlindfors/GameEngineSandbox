#include "GameOverScene.hpp"
#include "scenes/ISceneManager.hpp"
#include "input/IInputManager.hpp"
#include "renderers/SpriteRenderer.hpp"
#include "sprites/Sprite.hpp"
#include "utilities/IOC.hpp"
#include "game/IGameStateCallback.hpp"
#include "utilities/ITweenEngine.hpp"
#include "renderers/FontRenderer.hpp"
#include "systems/ScoreSystem.hpp"
#include "resources/IResourceManager.hpp"
#include "utilities/Logger.hpp"

using namespace std;
using namespace Engine;
using namespace Engine;

GameOverScene::GameOverScene(IGameStateCallback *gameCallback)
	: mGameOverText(make_shared<Sprite>()), mScoreBoard(make_shared<Sprite>()), mMedal(make_shared<Sprite>()), mButton(make_shared<Sprite>()), mGame(gameCallback), mInputManager(IOCContainer::instance().resolve<IInputManager>()), mTweenEngine(IOCContainer::instance().resolve<ITweenEngine>()), mFontRenderer(IOCContainer::instance().resolve<FontRenderer>()), mScoreSystem(IOCContainer::instance().resolve<ScoreSystem>())
{
	id = typeid(GameOverScene).name();
}

GameOverScene::~GameOverScene()
{
	mTweenEngine->clear();
}

void GameOverScene::load()
{
	debuglog << "[GameOverScene::load]" << endl;
	auto resourceManager = IOCContainer::instance().resolve<IResourceManager>();
	auto texture = resourceManager->getTexture("atlas.png");
	mGameOverText->texture = texture;
	mButton->texture = texture;
	mScoreBoard->texture = texture;
	mMedal->texture = texture;

	mGameOverText->size = {48.0f, 12.0f};
	mGameOverText->offset = {
		1.0f / 512.0f, (512.0f - 153.0f) / 512.0f,
		192.0f / 512.0f, 48.0f / 512.0f}; // 1, 105, 193, 153

	mButton->size = {104.0f, 58.0f};
	mButton->position = Point<float>{92.0f, 176.0f};
	mButton->offset = {
		2.0f / 512.0f, (512.0f - 351.0f) / 512.0f,
		104.0f / 512.0f, 58.0f / 512.0f}; // 2, 293, 106, 351

	mScoreBoard->size = {225.0f, 113.0f};
	mScoreBoard->position = Point<float>{144.0f - mScoreBoard->size.width / 2.0f, 250.0f};
	mScoreBoard->offset = {
		53.0f / 512.0f, (512.0f - 287.0f) / 512.0f,
		225.0f / 512.0f, 113.0f / 512.0f}; // 53, 174, 278, 287

	mMedal->size = {44.0f, 44.0f};
	mMedal->position = mScoreBoard->position + Point<float>{25.0f, 25.0f};
	mMedal->offset = {
		2.0f / 512.0f, (512.0f - 217.0f) / 512.0f,
		44.0f / 512.0f, 44.0f / 512.0f}; // 2, 173, 46, 217

	mTweenEngine->add(
		mGameOverText->size.width, 192.0f, [&](const auto value)
		{ mGameOverText->size.width = value; },
		1500, true);
	mTweenEngine->add(
		mGameOverText->size.height, 48.0f, [&](const auto value)
		{ mGameOverText->size.height = value; },
		1500, true);
}

void GameOverScene::unload() {}

void GameOverScene::updateScreenSize(int width, int height) {}

void GameOverScene::handleInput()
{
	auto const mouseState = mInputManager->getMouseState();
	if (mouseState.state == ButtonState::Pressed)
	{
		Engine::Point<int> position = {mouseState.position.x, 505 - mouseState.position.y};
		if (position.x > 92 &&
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
	mGameOverText->position = {288.0f / 2.0f - mGameOverText->size.width / 2.0f,
							   505.0f / 2.0f - mGameOverText->size.height / 2.0f + 150.0f};
	handleInput();
}

void GameOverScene::draw(shared_ptr<IRenderer> renderer)
{
	auto spriteRenderer = static_pointer_cast<SpriteRenderer>(renderer);
	auto score = mScoreSystem->getLatestScore();
	if (spriteRenderer)
	{
		spriteRenderer->drawSprite(mGameOverText);
		spriteRenderer->drawSprite(mButton);
		spriteRenderer->drawSprite(mScoreBoard);
		if (score >= 10)
		{
			if (score >= 20)
			{
				mMedal->offset = {
					2.0f / 512.0f, (512.0f - 265.0f) / 512.0f,
					44.0f / 512.0f, 44.0f / 512.0f}; // 2, 221, 46, 265
			}
			spriteRenderer->drawSprite(mMedal);
		}
		mFontRenderer->drawString(to_string(score), FontRenderer::Alignment::Center, Point<float>{mScoreBoard->position.x + 200, mScoreBoard->position.y + 68}, 0.3f);
		mFontRenderer->drawString(to_string(mScoreSystem->getHighScore()), FontRenderer::Alignment::Center, Point<float>{mScoreBoard->position.x + 200, mScoreBoard->position.y + 18}, 0.3f);
	}
}
