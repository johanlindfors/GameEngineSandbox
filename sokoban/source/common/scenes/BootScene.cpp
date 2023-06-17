#include "BootScene.hpp"
#include <memory>
#include <cpr/cpr.h>
#include "game/IGameStateCallback.hpp"
#include "resources/IResourceManager.hpp"
#include "renderers/Camera.hpp"
#include "renderers/SpriteRenderer.hpp"
#include "utilities/Config.hpp"
#include "utilities/IOC.hpp"
#include "game/GameDefines.hpp"
#include "objects/Map.hpp"

#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>

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
    resourceManager->loadTextures({ "tiles.png" });
    
    auto config = IOCContainer::instance().resolve<Utilities::Config>();
    auto camera = make_shared<Engine::OrthographicCamera>( 0.0f, config->width, 0.0f, config->height, -1.0f, 1.0f );
    auto shader = resourceManager->getShader( "simple" );
    auto renderer = make_shared<SpriteRenderer>( shader, camera );
    renderer->initialize();
    IOCContainer::instance().register_type<IRenderer>(renderer);

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
    // TODO: Fetch level from backend, register level in IoC?
    if(mInitialized) {
        printf("[BootScene::update] Fetching level from server\n");
        cpr::Response r = cpr::Get(cpr::Url{"https://www.programmeramera.se/pages/sokobants/assets/001.txt"});
        std::string result;
        if(r.status_code == 200) {
            printf("[BootScene::update] Fetched level from server\n");
            result = r.text;
        } else {
            result = "\
##########\r\n\
#####  ..#\r\n\
##### $  #\r\n\
####    .#\r\n\
###  $   #\r\n\
###     .#\r\n\
#     ####\r\n\
# $ $ @###\r\n\
##       #\r\n\
##########\r\n";
            printf("[BootScene::update] Failed to fetch level\n");
        }
        IOCContainer::instance().register_type<Map>(Map::parse(result));
        mGame->goToState(GameState::GamePlay);
    }
}

void BootScene::draw(std::shared_ptr<Engine::IRenderer> renderer)
{}