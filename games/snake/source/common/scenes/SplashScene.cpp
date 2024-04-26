#include "SplashScene.hpp"
#include "utilities/IOC.hpp"
#include "utilities/IStepTimer.hpp"
#include "utilities/Config.hpp"
#include "utilities/Logger.hpp"
#include "scenes/ISceneManager.hpp"
#include "game/IGameStateCallback.hpp"
#include "resources/IResourceManager.hpp"
#include "renderers/SpriteRenderer.hpp"
#include "sprites/Sprite.hpp"
#include "renderers/Camera.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;

SplashScene::SplashScene(IGameStateCallback *gameCallback)
	: mSprite(make_shared<Sprite>()), mMillisecondsToLoad(2000.0f), hasLoadedGamePlay(false), isLoadingResources(false), mGame(gameCallback)
{
	id = typeid(SplashScene).name();
}

SplashScene::~SplashScene() {}

void SplashScene::load()
{
	mResourceManager = IOCContainer::instance().resolve<IResourceManager>();

	vector<string> fileNames;
	fileNames.emplace_back("coderox.png");
	mResourceManager->loadTextures(vector<string>(fileNames));

	mResourcesToLoad.push("apple.png");
	mResourcesToLoad.push("snake.png");
	mResourcesToLoad.push("gameover/background.png");
	mResourcesToLoad.push("gameover/text.png");
	mResourcesToLoad.push("pause/background.png");
	mResourcesToLoad.push("pause/text.png");

	mSprite->texture = mResourceManager->getTexture("coderox.png");

	mResourceManager->loadShader("simple", "simple.vs", "simple.fs");
	mResourceManager->loadSounds({"score.wav"});

	auto config = IOCContainer::instance().resolve<Utilities::Config>();
	auto camera = make_shared<Engine::OrthographicCamera>(0.0f, config->width, 0.0f, config->height, -1.0f, 1.0f);
	auto shader = mResourceManager->getShader("simple");
	auto renderer = make_shared<SpriteRenderer>(shader, camera);
	renderer->initialize();
	IOCContainer::instance().register_type<IRenderer>(renderer);

	debuglog << "[SplashScene::load] Loaded" << endl;
}

void SplashScene::unload() {}

void SplashScene::updateScreenSize(int width, int height)
{
	const auto spriteAspectRatio = static_cast<float>(mSprite->texture.height) / static_cast<float>(mSprite->texture.width);
	const auto screenAspectRatio = static_cast<float>(height) / static_cast<float>(width);
	if (screenAspectRatio > spriteAspectRatio)
	{
		mSprite->size = {
			static_cast<float>(width * spriteAspectRatio),
			static_cast<float>(width)};
	}
	else
	{
		mSprite->size = {
			static_cast<float>(height),
			static_cast<float>(height / spriteAspectRatio)};
	}
	mSprite->position = {static_cast<float>(width / 2.0f - mSprite->size.width / 2.0f),
						 static_cast<float>(height / 2.0f - mSprite->size.height / 2.0f)};
}

void SplashScene::update(shared_ptr<IStepTimer> timer)
{
	if (mResourcesToLoad.size() > 0)
	{
		debuglog << "[SplashScene::Update] Loading resources" << endl;

		isLoadingResources = true;
		vector<string> fileNames;
		fileNames.emplace_back(mResourcesToLoad.front());
		mResourcesToLoad.pop();
		mResourceManager->loadTextures(vector<string>(fileNames));
		isLoadingResources = false;
		debuglog << "[SplashScene::Update] Resources loaded" << endl;
	}
	mMillisecondsToLoad -= static_cast<float>((timer->getElapsedSeconds() * 1000.0f));
	if (mMillisecondsToLoad <= 0 && mResourcesToLoad.size() == 0)
	{
		auto sceneManager = IOCContainer::instance().resolve<ISceneManager>();
		if (!hasLoadedGamePlay)
		{
			mGame->goToState(GameState::GamePlay);
			hasLoadedGamePlay = true;
		}
	}
}

void SplashScene::draw(shared_ptr<IRenderer> renderer)
{
	auto spriteRenderer = static_pointer_cast<SpriteRenderer>(renderer);
	if (spriteRenderer && !isLoadingResources)
	{
		spriteRenderer->drawSprite(mSprite);
	}
}