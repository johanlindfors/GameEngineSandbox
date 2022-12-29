#pragma once
#include <string>
#include <vector>

#include "utilities/IOC.hpp"
#include "utilities/Config.h"
#include "GameStateMachine.h"
#include "GameDefines.h"
#include "renderers/SimpleRenderer.h"
#include "resources/ResourceManager.h"
#include "filesystem/FileSystem.h"

using namespace std;
using namespace Engine;
using namespace Utilities;

void Bootstrap() {
    auto config = make_shared<Config>();
    config->FPS = 60;
    config->UseFixedTimeStep = false;
    config->Width = SCREEN_WIDTH;
    config->Height = SCREEN_HEIGHT;
    config->Title = "Sample 3d Scene";
    
    IOCContainer::Instance().Register<Config>(config);
    IOCContainer::Instance().Register<IRenderer>(make_shared<SimpleRenderer>());

    const auto fileSystem = make_shared<FileSystem>();
	IOCContainer::Instance().Register<IFileSystem>(fileSystem);

    const auto  resourceManager = make_shared<ResourceManager>();
    resourceManager->LoadShader("basic_lighting", "basic_lighting.vs", "basic_lighting.fs");
	resourceManager->LoadShader("light_cube", "light_cube.vs", "light_cube.fs");
    IOCContainer::Instance().Register<IResourceManager>(resourceManager);
    IOCContainer::Instance().Register<IGameLoopCallback>(make_shared<GameStateMachine>());
}