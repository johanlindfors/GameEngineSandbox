#pragma once
#include <string>
#include <vector>

#include "utilities/IOC.hpp"
#include "utilities/Config.h"
#include "Game.h"
#include "GameDefines.h"
#include "renderers/SimpleRenderer.h"
#include "resources/ResourceManager.h"
#include "filesystem/FileSystem.h"

using namespace std;
using namespace Engine;
using namespace Utilities;

void bootstrap() {
    auto config = make_shared<Config>();
    config->fps = 2;
    config->useFixedTimeStep = false;
    config->width = SCREEN_WIDTH;
    config->height = SCREEN_HEIGHT;
    config->title = "Sample 3d Scene";
    config->glMajorVersion = 3;
    config->glMinorVersion = 2;
    
    IOCContainer::instance().register_type<Config>(config);
    IOCContainer::instance().register_type<IGameLoopCallback>(make_shared<Sample::Game>());
    
    IOCContainer::instance().register_type<IRenderer>(make_shared<Engine::SimpleRenderer>());
}