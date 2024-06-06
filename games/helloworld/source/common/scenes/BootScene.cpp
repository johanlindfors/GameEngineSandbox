#include "BootScene.hpp"

//#include <emscripten.h>

// Engine
#include "utilities/Logger.hpp"
#include "utilities/IOC.hpp"
#include "scenes/ISceneManager.hpp"
#include "renderers/SpriteRenderer.hpp"

// Game
#include "game/GameDefines.hpp"
#include "scenes/SpriteScene.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;
using namespace HelloWorld::Scenes;

// void onLoaded(const char* file) {
//     auto resourceDownloader = IOCContainer::instance().resolve<ResourceDownloader>();
//     resourceDownloader->downloadNext();
// }

// void onError(const char* file) {
//     auto resourceDownloader = IOCContainer::instance().resolve<ResourceDownloader>();
//     resourceDownloader->reportError();
// }

// void ResourceDownloader::downloadNext()
// {
//     debuglog << "[ResourceDownloader::downloadNext] In downloadNext" << endl;
//     if (mFetchedResources == mResources.size()) {
//         mCallbackInstance->complete();
//     } else {
//         auto httpFileName = string("http://localhost:6931/") + string(mResources[mFetchedResources]);
//         debuglog << "[ResourceDownloader::downloadNext] Fetching file '" << httpFileName << "' from server." << endl;
//         emscripten_async_wget(
//             httpFileName.c_str(), 
//             mResources[mFetchedResources].c_str(),
//             onLoaded,
//             onError
//         );
//         mFetchedResources++;
//     }
// }

// void ResourceDownloader::reportError()
// {
//     debuglog << "[ResourceDownloader::reportError] In reportError" << endl;
//     mCallbackInstance->error();
// }

void BootScene::load()
{
    debuglog << "[BootScene::load] In load" << endl;
    // std::vector<std::string> resources = {
    //     "assets/textures/grid.png", 
    //     "assets/shaders/simple.vs",
    //     "assets/shaders/simple.fs"
    // };
    // auto resourceDownloader = make_shared<ResourceDownloader>(this, resources);
    // IOCContainer::instance().register_type<ResourceDownloader>(resourceDownloader);
    // resourceDownloader->downloadNext();
}

void BootScene::unload() 
{
    debuglog << "[BootScene::unload] In unload" << endl;
    //IOCContainer::instance().remove<ResourceDownloader>();
}

void BootScene::updateScreenSize(int width, int height)
{
    debuglog << "[BootScene::updateScreenSize] Width: " << width << " Height: " << height << endl;
}

// void BootScene::complete()
// {
//     debuglog << "[BootScene::complete] In complete" << endl;
//     mResourcesLoaded = true;
// }

// void BootScene::error()
// {
//     debuglog << "[BootScene::error] In error" << endl;
// }   

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
