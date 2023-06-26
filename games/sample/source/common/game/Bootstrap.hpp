#pragma once
#include <string>
#include <vector>

#include "utilities/IOC.hpp"
#include "utilities/Config.hpp"
#include "Game.hpp"
#include "GameDefines.hpp"
#include "renderers/SimpleRenderer.hpp"
#include "resources/ResourceManager.hpp"
#include "filesystem/FileSystem.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;

void bootstrap() {
    auto config = make_shared<Config>();
    config->fps = FRAMES_PER_SECOND;
    config->useFixedTimeStep = false;
    config->width = SCREEN_WIDTH;
    config->height = SCREEN_HEIGHT;
    config->title = "Sample 3d Scene";
    config->executable = "sample";
    config->glMajorVersion = 3;
    config->glMinorVersion = 3;
    
    IOCContainer::instance().register_type<Config>(config);
    IOCContainer::instance().register_type<IGameLoopCallback>(make_shared<Sample::Game>());
    
    //IOCContainer::instance().register_type<IRenderer>(make_shared<Engine::SimpleRenderer>());
}