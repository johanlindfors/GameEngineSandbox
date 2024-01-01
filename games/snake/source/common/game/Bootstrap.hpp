#pragma once
#include "utilities/IOC.hpp"
#include "game/Game.hpp"
#include "utilities/Config.hpp"

using namespace std;
using namespace Engine;

void bootstrap()
{
    auto config = make_shared<Config>();
    config->width = 500;
    config->height = 500;
    config->fps = 30;
    config->useFixedTimeStep = true;
    config->executable = "snake";
    config->glMajorVersion = 3;
    config->glMinorVersion = 3;
    IOCContainer::instance().register_type<Config>(config);
    IOCContainer::instance().register_type<IGameLoopCallback>(make_shared<Game>());
}
