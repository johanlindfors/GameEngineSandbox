#include "BootScene.hpp"

// Engine
#include "utilities/Logger.hpp"
#include "utilities/IOC.hpp"
#include "scenes/ISceneManager.hpp"
#include "renderers/SpriteRenderer.hpp"
#include "resources/ResourceDownloader.hpp"
#include "game/IGameStateCallback.hpp"

// Game
#include "game/GameDefines.hpp"
#include "game/GameState.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;

BootScene::BootScene(IGameStateCallback *gameCallback)
    : mGame(gameCallback)
{
	id = typeid(BootScene).name();
    debuglog << "[BootScene::BootScene] In constructor" << endl;
}

BootScene::~BootScene()
{
    debuglog << "[BootScene::~BootScene] In destructor" << endl;
}

void BootScene::load()
{
    debuglog << "[BootScene::load] In load" << endl;
    const std::vector<std::string> resources = {
        // textures
        "assets/textures/apple.png", 
        "assets/textures/coderox.png",
        "assets/textures/snake.png",
        "assets/textures/gameover/background.png",
        "assets/textures/gameover/text.png",
        "assets/textures/pause/background.png",
        "assets/textures/pause/text.png",
        
        // shaders
        "assets/shaders/simple.vs",
        "assets/shaders/simple.fs",

        // audio
        "assets/audio/score.wav"
    };
    auto resourceDownloader = make_shared<ResourceDownloader>(
        [&](bool success) { 
            if(success) {
                debuglog << "[BootScene::onComplete] Download completed" << endl;
                mResourcesLoaded = true;
            } else {
                debuglog << "[BootScene::complete] Download failed" << endl;
            }
        },
        [&](int progress) { 
            debuglog << "[BootScene::progress] Progress: " << progress << endl;
         }
    );

    IOCContainer::instance().register_type<ResourceDownloader>(resourceDownloader);
    resourceDownloader->downloadResources(resources);
}

void BootScene::unload() 
{
    debuglog << "[BootScene::unload] In unload" << endl;
    IOCContainer::instance().remove<ResourceDownloader>();
}

void BootScene::updateScreenSize(int width, int height)
{
    debuglog << "[BootScene::updateScreenSize] Width: " << width << " Height: " << height << endl;
}

void BootScene::update(std::shared_ptr<Utilities::IStepTimer> timer)
{
    if (mResourcesLoaded) {
        debuglog << "[BootScene::update] Going to splash" << endl;
        mGame->goToState(GameState::Splash);
    }
}

void BootScene::draw(std::shared_ptr<Engine::IRenderer> renderer)
{
    debuglog << "[BootScene::draw] In draw" << endl;
    auto spriteRenderer = static_pointer_cast<SpriteRenderer>(renderer);
	spriteRenderer->clear(CORNFLOWER_BLUE);
}
