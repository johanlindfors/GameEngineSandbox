#include "SplashScene.hpp"
#include "utilities/IOC.hpp"
#include "scenes/ISceneManager.hpp"
#include "game/IGameStateCallback.hpp"
#include "resources/IResourceManager.hpp"
#include "input/IInputManager.hpp"
#include "renderers/SpriteRenderer.hpp"
#include "sprites/Sprite.hpp"
#include "utilities/IStepTimer.hpp"
#include "objects/ParallaxBackground.hpp"
#include "objects/Bird.hpp"
#include "objects/Ground.hpp"
#include "utilities/Config.hpp"
#include "renderers/Camera.hpp"
#include "renderers/FontRenderer.hpp"
#include "systems/ScoreSystem.hpp"
#include "utilities/Logger.hpp"

#include "utilities/ALHelper.hpp"
#include "resources/Sound.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;

SplashScene::SplashScene(IGameStateCallback *gameCallback)
	: mSkyline(make_shared<ParallaxBackground>())
	, mGround(make_shared<Ground>(Point<float>{0, 79}, Vector2{SCROLL_SPEED, 0}))
	, mTitle(make_shared<Sprite>())
	, mButton(make_shared<Sprite>())
	, mBird(make_shared<Bird>(Point<float>{0, 0}))
	, mMillisecondsToLoad(2000.0f)
	, mHasLoadedGamePlay(false)
	, mIsLoadingResources(true)
	, mWindowWidth(0)
	, mWindowHeight(0)
	, mGame(gameCallback)
{
	id = typeid(SplashScene).name();

	// mButton->offset = 12;
	mButton->size = {104.0f, 58.0f};
	mButton->position = Point<float>{92.0f, 176.0f};
	mButton->offset = {
		2.0f / 512.0f, (512.0f - 351.0f) / 512.0,
		104.0f / 512.0f, 58.0 / 512.0f};

	// mTitle->offset = 13;
	mTitle->size = {179.0f, 48.0f};
	mTitle->offset = {
		116.0f / 512.0f, (512.0f - 346.0f) / 512.0f,
		179.0f / 512.0f, 48.0f / 512.0f}; // 116, 298, 295, 346
}

SplashScene::~SplashScene()
{
	mSkyline.reset();
	mGround.reset();
	mTitle.reset();
	mButton.reset();
	mBird.reset();
}

void SplashScene::load()
{
	auto resourceManager = IOCContainer::instance().resolve<IResourceManager>();
	mInputManager = IOCContainer::instance().resolve<IInputManager>();

	resourceManager->loadShader("simple", "simple.vs", "simple.fs");
	debuglog << "[SplashScene::load] Shader Loaded" << endl;
	resourceManager->loadTextures({"atlas.png"});

	auto config = IOCContainer::instance().resolve<Utilities::Config>();
	auto camera = make_shared<Engine::OrthographicCamera>(0.0f, static_cast<float>(config->width), 0.0f, static_cast<float>(config->height), -1.0f, 1.0f);
	auto shader = resourceManager->getShader("simple");
	auto renderer = make_shared<SpriteRenderer>(shader, camera);
	renderer->initialize();
	IOCContainer::instance().register_type<IRenderer>(renderer);

	auto fontRenderer = make_shared<FontRenderer>("textures/numbers.fnt", "atlas.png", shader, camera);
	fontRenderer->initialize();
	IOCContainer::instance().register_type<FontRenderer>(fontRenderer);

	auto atlas = resourceManager->getTexture("atlas.png");
	mButton->texture.textureIndex = atlas.textureIndex;
	mTitle->texture.textureIndex = atlas.textureIndex;
	mBird->initializeSprite();
	mGround->initializeSprite();
	mSkyline->initializeSprites();

    auto scoreSystem = make_shared<ScoreSystem>();
    IOCContainer::instance().register_type<ScoreSystem>(scoreSystem);
	scoreSystem->loadHighScore();
	
	// Audio
	resourceManager->loadSounds({"flap.wav", "ground-hit.wav", "ouch.wav", "pipe-hit.wav", "score.wav"});
	
	debuglog << "[SplashScene::load] Loaded" << endl;
}

void SplashScene::unload() {}

void SplashScene::updateScreenSize(int width, int height)
{
	if (mWindowWidth == width && mWindowHeight == height)
		return;

	mTitle->position = Point<float>{30.0f, height - 100.0f - mTitle->size.height};
	mBird->position = Point<float>{230.0f, height - 129.0f};

	mWindowWidth = width;
	mWindowHeight = height;
}

void SplashScene::update(shared_ptr<IStepTimer> timer)
{
	auto milliseconds = static_cast<float>(timer->getElapsedMilliSeconds());
	mMillisecondsToLoad -= milliseconds;
	mSkyline->update(timer);
	mGround->update(timer);

	auto const mouseState = mInputManager->getMouseState();
	if (mouseState.state == ButtonState::Pressed)
	{
		Utilities::Point<int> position = {mouseState.position.x, 505 - mouseState.position.y};
		if (position.x > 92 &&
			position.x < 92 + 104 &&
			position.y > 176 &&
			position.y < 176 + 58)
		{
			mGame->goToState(GameState::Instructions);
		}
	}
}

void SplashScene::draw(shared_ptr<IRenderer> renderer)
{	
	renderer->clear(BACKGROUND_COLOR);
	
	auto spriteRenderer = static_pointer_cast<SpriteRenderer>(renderer);
	mSkyline->draw(renderer);
	mGround->draw(renderer);
	mBird->draw(renderer);
	if (spriteRenderer)
	{
		spriteRenderer->drawSprite(mTitle);
		spriteRenderer->drawSprite(mButton);
	}
}
