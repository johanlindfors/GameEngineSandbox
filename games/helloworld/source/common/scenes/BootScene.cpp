#include "scenes/BootScene.hpp"

// Engine
#include "utilities/Logger.hpp"
#include "utilities/IOC.hpp"
#include "scenes/ISceneManager.hpp"
#include "renderers/SpriteRenderer.hpp"
#if EMSCRIPTEN
#include "resources/ResourceDownloader.hpp"
#endif
// Game
#include "game/GameDefines.hpp"
#include "scenes/SpriteScene.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;
using namespace HelloWorld::Scenes;

void BootScene::load()
{
    debuglog << "[BootScene::load] In load" << endl;
#if EMSCRIPTEN
    const std::vector<std::string> resources = {
        "assets/textures/grid.png", 
        "assets/shaders/framebuffer.vs",
        "assets/shaders/framebuffer.fs",
        "assets/shaders/simple.vs",
        "assets/shaders/simple.fs"
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
#else
    mResourcesLoaded = true;
#endif
}

void BootScene::unload() 
{
    debuglog << "[BootScene::unload] In unload" << endl;
#if EMSCRIPTEN
    IOCContainer::instance().remove<ResourceDownloader>();
#endif
}

void BootScene::updateScreenSize(int width, int height)
{
    debuglog << "[BootScene::updateScreenSize] Width: " << width << " Height: " << height << endl;
}

void BootScene::update(std::shared_ptr<Utilities::IStepTimer> timer)
{
    debuglog << "[BootScene::update] In update" << endl;

    if (mResourcesLoaded) {
        auto sceneManager = IOCContainer::instance().resolve<ISceneManager>();
        sceneManager->addScene(make_shared<SpriteScene>());
        sceneManager->removeScene(typeid(BootScene));
    }
}

void BootScene::draw(std::shared_ptr<Engine::IRenderer> renderer)
{
    debuglog << "[BootScene::draw] In draw" << endl;
    auto spriteRenderer = static_pointer_cast<SpriteRenderer>(renderer);
	spriteRenderer->clear(CORNFLOWER_BLUE);
}
