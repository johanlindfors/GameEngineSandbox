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
#include "utilities/Logger.hpp"
#include "http/IHttpClient.hpp"
#include "resources/ResourceDownloader.hpp"

// game
#include "game/IGameStateCallback.hpp"
#include "game/GameDefines.hpp"
#include "objects/Map.hpp"

using namespace std;
using namespace std::chrono;
using namespace Engine;
using namespace Utilities;

BootScene::BootScene(IGameStateCallback *gameCallback)
    : mGame(gameCallback), mInitialized(false), mLoadedTasks(0)
{
    id = typeid(BootScene).name();
}

BootScene::~BootScene()
{
    debuglog << "[BootScene::~BootScene] In destructor" << endl;
    // throw new std::runtime_error("[BootScene::~BootScene] in destructore");
}


void BootScene::load()
{
    debuglog << "[BootScene::load]" << endl;

#if EMSCRIPTEN
    mLoadingTasks.push([&]() {
        debuglog << "[BootScene::load] Downloading resources..." << endl;

        const std::vector<std::string> resources = {
            "assets/fonts/vga_16x16.fnt",
            string("assets/textures/") + string(TILES),
            string("assets/textures/") + string(FONT),
            "assets/shaders/simple.vs",
            "assets/shaders/simple.fs"
        };
        auto resourceDownloader = make_shared<ResourceDownloader>(
            [&](bool success) { 
                if(success) {
                    debuglog << "[BootScene::onComplete] Download completed" << endl;
                    mPreviousTaskFinished = true;
                } else {
                    debuglog << "[BootScene::complete] Download failed" << endl;
                }
                IOCContainer::instance().remove<ResourceDownloader>();
            },
            [&](int progress) { 
                debuglog << "[BootScene::progress] Progress: " << progress << endl;
            }
        );
        IOCContainer::instance().register_type<ResourceDownloader>(resourceDownloader);
        resourceDownloader->downloadResources(resources);
    });
#else
    mPreviousTaskFinished = true;
#endif

    mLoadingTasks.push([this]() {    
        debuglog << "[BootScene::load] Loading shader" << endl;
        auto resourceManager = IOCContainer::instance().resolve<IResourceManager>();
        resourceManager->loadShader( "simple", "simple.vs", "simple.fs" );

        mLoadedTasks++;
        mPreviousTaskFinished = true;
    });

    mLoadingTasks.push([&]() {    
        debuglog << "[BootScene::load] Loading textures" << endl;
        auto resourceManager = IOCContainer::instance().resolve<IResourceManager>();
        resourceManager->loadTextures({ TILES, FONT });

        mLoadedTasks++;
        mPreviousTaskFinished = true;
    });

    mLoadingTasks.push([&]() {
        auto resourceManager = IOCContainer::instance().resolve<IResourceManager>();
        auto config = IOCContainer::instance().resolve<Utilities::Config>();
        auto camera = make_shared<Engine::OrthographicCamera>( 0.0f, config->width, 0.0f, config->height, -1.0f, 1.0f );
        IOCContainer::instance().register_type<OrthographicCamera>(camera);

        mLoadedTasks++;
        mPreviousTaskFinished = true;
    });

    mLoadingTasks.push([&]() {
        auto resourceManager = IOCContainer::instance().resolve<IResourceManager>();
        auto shader = resourceManager->getShader( "simple" );
        auto camera = IOCContainer::resolve_type<OrthographicCamera>();
        auto fontRenderer = make_shared<FontRenderer>("fonts/vga_16x16.fnt", FONT, shader, camera);
        fontRenderer->initialize();
        IOCContainer::instance().register_type<FontRenderer>(fontRenderer);

        mLoadedTasks++;
        mPreviousTaskFinished = true;
    });

    mLoadingTasks.push([&]() {
        auto resourceManager = IOCContainer::instance().resolve<IResourceManager>();
        auto shader = resourceManager->getShader( "simple" );
        auto camera = IOCContainer::resolve_type<OrthographicCamera>();
        auto renderer = make_shared<SpriteRenderer>( shader, camera );
        renderer->initialize();
        IOCContainer::instance().register_type<IRenderer>(renderer);

        this_thread::sleep_for(LOADING_PAUSE);
        mLoadedTasks++;
            mPreviousTaskFinished = true;
    });

    for (int i = 0; i < 10; i++) {
        mLoadingTasks.push([&]()
                           {
            this_thread::sleep_for(LOADING_PAUSE);
            mLoadedTasks++; 
            mPreviousTaskFinished = true;
        });
    }

    mLoadingTasks.push([&]() {
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

        // this_thread::sleep_for(LOADING_PAUSE);
        mLoadedTasks++;
        mPreviousTaskFinished = true;
        mInitialized = true;
    });

    mTotalTasks = mLoadingTasks.size();
}

void BootScene::unload()
{
    debuglog << "[BootScene::unload]" << endl;
}

void BootScene::updateScreenSize(int width, int height)
{
}

void BootScene::update(std::shared_ptr<Utilities::IStepTimer> timer)
{
    debuglog << "[BootScene::update]" << endl;
    if (mInitialized)
    {
        mGame->goToState(GameState::GamePlay);
    }
    else
    {
        if (mPreviousTaskFinished && !mLoadingTasks.empty())
        {
            mPreviousTaskFinished = false;
            std::function<void()> loadingTask = mLoadingTasks.front();
            mLoadingTasks.pop();
            mLoaded = to_string(static_cast<int>(mLoadedTasks / static_cast<float>(mTotalTasks) * 100)) + "%";
            loadingTask();
            this_thread::sleep_for(microseconds(1500));
        }
    }
}

void BootScene::draw(std::shared_ptr<Engine::IRenderer> renderer)
{
    debuglog << "[BootScene::draw]" << endl;
    renderer->clear(0,0,0,1);
    if (IOCContainer::instance().contains<FontRenderer>())
    {
        auto fontRenderer = IOCContainer::resolve_type<FontRenderer>();
        fontRenderer->drawString(mLoaded, FontRenderer::Alignment::Center, {200, 200}, 2.0);
    }
}
