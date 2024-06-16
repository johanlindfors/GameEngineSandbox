#include "BootScene.hpp"

// Engine
#include "utilities/Logger.hpp"
#include "utilities/IOC.hpp"
#include "scenes/ISceneManager.hpp"
#include "renderers/SpriteRenderer.hpp"
#include "resources/ResourceDownloader.hpp"

// Game
#include "game/GameDefines.hpp"
#include "scenes/SpriteScene.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;
using namespace Sample;

BootScene::BootScene()
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
        "assets/textures/coderox.png", 
        "assets/textures/truesec.png",
        
        // shaders
        "assets/shaders/model.vs",
        "assets/shaders/model.fs",
        "assets/shaders/simple.vs",
        "assets/shaders/simple.fs",

        // models
        "assets/models/cube.mdl"
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
        auto sceneManager = IOCContainer::instance().resolve<ISceneManager>();
        sceneManager->removeScene(typeid(BootScene));
        sceneManager->addScene(make_shared<SpriteScene>());
    }
}

void BootScene::draw(std::shared_ptr<Engine::IRenderer> renderer)
{
    debuglog << "[BootScene::draw] In draw" << endl;
    auto spriteRenderer = static_pointer_cast<SpriteRenderer>(renderer);
	spriteRenderer->clear(CORNFLOWER_BLUE);
}
