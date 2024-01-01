#pragma once
#include "utilities/IOC.hpp"
#include "utilities/Config.hpp"
#include "Game.hpp"
#include "GameDefines.hpp"

using namespace std;
using namespace Engine;

void bootstrap() {
    auto config = make_shared<Config>();
    config->fps = FRAMES_PER_SECOND;
    config->useFixedTimeStep = false;
    config->width = SCREEN_WIDTH;
    config->height = SCREEN_HEIGHT;
    config->title = "Hello World";
    config->glMajorVersion = 3;
    config->glMinorVersion = 3;
    config->useFixedGameSize = true;

    IOCContainer::instance().register_type<Config>(config);
    IOCContainer::instance().register_type<IGameLoopCallback>(make_shared<Game>());
}