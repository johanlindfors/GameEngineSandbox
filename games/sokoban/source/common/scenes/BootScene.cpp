#include "BootScene.hpp"
#include <chrono>
#include <thread>

// engine
#include "resources/IResourceManager.hpp"
#include "renderers/Camera.hpp"
#include "renderers/SpriteRenderer.hpp"
#include "renderers/FontRenderer.hpp"
#include "utilities/Config.hpp"
#include "utilities/IOC.hpp"
#include "http/IHttpClient.hpp"

// game
#include "game/IGameStateCallback.hpp"
#include "game/GameDefines.hpp"
#include "objects/Map.hpp"
#include "utilities/Logger.hpp"

using namespace std;
using namespace Engine;

BootScene::BootScene(IGameStateCallback *gameCallback)
    : mGame(gameCallback), mInitialized(false), mLoadedTasks(0)
{
    id = typeid(BootScene).name();
}

void BootScene::load()
{
    debuglog << "[BootScene::load]" << endl;

    mLoadingTasks.push([&]()
                       {    
        auto resourceManager = IOCContainer::instance().resolve<IResourceManager>();
        resourceManager->loadShader( "simple", "simple.vs", "simple.fs" );

        mLoadedTasks++; });

    mLoadingTasks.push([&]()
                       {    
        auto resourceManager = IOCContainer::instance().resolve<IResourceManager>();
        resourceManager->loadTextures({ TILES, FONT });

        mLoadedTasks++; });

    mLoadingTasks.push([&]()
                       {
        auto resourceManager = IOCContainer::instance().resolve<IResourceManager>();
        auto config = IOCContainer::instance().resolve<Engine::Config>();
        auto camera = make_shared<Engine::OrthographicCamera>( 0.0f, config->width, 0.0f, config->height, -1.0f, 1.0f );
        IOCContainer::instance().register_type<OrthographicCamera>(camera);

        mLoadedTasks++; });

    mLoadingTasks.push([&]()
                       {
        auto resourceManager = IOCContainer::instance().resolve<IResourceManager>();
        auto shader = resourceManager->getShader( "simple" );
        auto camera = IOCContainer::resolve_type<OrthographicCamera>();
        auto fontRenderer = make_shared<FontRenderer>("fonts/vga_16x16.fnt", FONT, shader, camera);
        fontRenderer->initialize();
        IOCContainer::instance().register_type<FontRenderer>(fontRenderer);

        mLoadedTasks++; });

    mLoadingTasks.push([&]()
                       {
        auto resourceManager = IOCContainer::instance().resolve<IResourceManager>();
        auto shader = resourceManager->getShader( "simple" );
        auto camera = IOCContainer::resolve_type<OrthographicCamera>();
        auto renderer = make_shared<SpriteRenderer>( shader, camera );
        renderer->initialize();
        IOCContainer::instance().register_type<IRenderer>(renderer);

        this_thread::sleep_for(LOADING_PAUSE);
        mLoadedTasks++; });

    for (int i = 0; i < 10; i++)
    {
        mLoadingTasks.push([&]()
                           {
            this_thread::sleep_for(LOADING_PAUSE);
            mLoadedTasks++; });
    }

    mLoadingTasks.push([&]()
                       {
        string result;

        if(IOCContainer::instance().contains<IHttpClient>()) {
            debuglog << "[BootScene::update] Fetching level from server" << endl;

            auto httpClient = IOCContainer::instance().resolve<IHttpClient>();
            string url("https://programmeramera.se/pages/sokobants/assets/003.txt");
            result = httpClient->get(url);

            if(result.length() == 0) {
                debuglog << "[BootScene::update] Failed to fetch level" << endl;
                result = HARD_MAP;
            }
        } else {
            result = HARD_MAP;
        }

        IOCContainer::instance().register_type<Map>(Map::parse(result));

        this_thread::sleep_for(LOADING_PAUSE);
        mLoadedTasks++;
        mInitialized = true; });

    mTotalTasks = mLoadingTasks.size();
}

void BootScene::unload()
{
    debuglog << "[BootScene::unload]" << endl;
}

void BootScene::updateScreenSize(int width, int height)
{
}

void BootScene::update(std::shared_ptr<Engine::IStepTimer> timer)
{
    if (mInitialized)
    {
        mGame->goToState(GameState::GamePlay);
    }
    else
    {
        if (!mLoadingTasks.empty())
        {
            debuglog << "[BootScene::update] running load task" << endl;
            std::function<void()> loadingTask = mLoadingTasks.front();
            loadingTask();
            mLoadingTasks.pop();
        }
    }
}

void BootScene::draw(std::shared_ptr<Engine::IRenderer> renderer)
{
    debuglog << "[BootScene::draw]" << endl;
    renderer->clear();

    if (IOCContainer::instance().contains<FontRenderer>())
    {
        auto fontRenderer = IOCContainer::resolve_type<FontRenderer>();
        string loaded(to_string(static_cast<int>(mLoadedTasks / static_cast<float>(mTotalTasks) * 100)) + "%");
        fontRenderer->drawString(loaded, FontRenderer::Alignment::Center, {200, 200}, 2.0);
    }
}
