#include "BootScene.hpp"

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


using namespace std;
using namespace Engine;
using namespace Utilities;

BootScene::BootScene(IGameStateCallback* gameCallback)
    : mGame(gameCallback)
    , mInitialized(false)
{
    id = typeid(BootScene).name();
}

void BootScene::load()
{
    printf("[BootScene::load]\n");
    auto resourceManager = IOCContainer::instance().resolve<IResourceManager>();
    
    resourceManager->loadShader( "simple", "simple.vs", "simple.fs" );
    resourceManager->loadTextures({ TILES });
    
    auto config = IOCContainer::instance().resolve<Utilities::Config>();
    auto camera = make_shared<Engine::OrthographicCamera>( 0.0f, config->width, 0.0f, config->height, -1.0f, 1.0f );
    auto shader = resourceManager->getShader( "simple" );
    auto renderer = make_shared<SpriteRenderer>( shader, camera );
    renderer->initialize();
    IOCContainer::instance().register_type<IRenderer>(renderer);

	IOCContainer::instance().resolve_type<IResourceManager>()->loadTextures({ FONT });

    auto fontRenderer = make_shared<FontRenderer>("fonts/vga_16x16.fnt", FONT, shader, camera);
    fontRenderer->initialize();
	IOCContainer::instance().register_type<FontRenderer>(fontRenderer);

    mInitialized = true;
}

void BootScene::unload()
{
    printf("[BootScene::unload]\n");
}

void BootScene::updateScreenSize(int width, int height)
{}

void BootScene::update(std::shared_ptr<Utilities::IStepTimer> timer)
{
    if(mInitialized) {
        string result;

        if(IOCContainer::instance().contains<IHttpClient>()) {
            printf("[BootScene::update] Fetching level from server\n");

            auto httpClient = IOCContainer::instance().resolve<IHttpClient>();
            string url("https://programmeramera.se/pages/sokobants/assets/003.txt");
            result = httpClient->get(url);

            if(result.length() == 0) {
                printf("[BootScene::update] Failed to fetch level\n");
                result = HARD_MAP;
            }
        } else {
            result = HARD_MAP;
        }

        IOCContainer::instance().register_type<Map>(Map::parse(result));

        // IOCContainer::instance().register_type<Map>(Map::parse(EASY_MAP), "easy");
        // IOCContainer::instance().register_type<Map>(Map::parse(MEDIUM_MAP), "medium");
        // IOCContainer::instance().register_type<Map>(Map::parse(HARD_MAP), "hard");
        mGame->goToState(GameState::GamePlay);
    }
}

void BootScene::draw(std::shared_ptr<Engine::IRenderer> renderer)
{}
