#pragma once
// thirdparty
#include <random>
#include <string>
#include <vector>
// engine
#include "filesystem/FileSystem.hpp"
#include "resources/ResourceManager.hpp"
#include "renderers/SimpleRenderer.hpp"
#include "utilities/Config.hpp"
#include "utilities/IOC.hpp"
// game
#include "Game.hpp"
#include "GameDefines.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;

void bootstrap() {
    std::srand ( (unsigned int)time(NULL) );

    auto config = make_shared<Config>();
    config->fps = FRAMES_PER_SECOND;
    config->useFixedTimeStep = true;
    config->width = SCREEN_WIDTH;
    config->height = SCREEN_HEIGHT;
    config->title = "Carcassone";
    config->executable = "carcassone";
    config->glMajorVersion = 3;
    config->glMinorVersion = 3;
    
    IOCContainer::instance().register_type<Config>(config);
    IOCContainer::instance().register_type<IGameLoopCallback>(make_shared<Sample::Game>());
}