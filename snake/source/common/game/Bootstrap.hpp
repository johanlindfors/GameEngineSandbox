#pragma once
#include "utilities/IOC.hpp"
#include "game/Game.h"
#include "utilities/Config.h"
#include "renderers/SpriteRenderer.h"

using namespace std;
using namespace Engine;
using namespace Utilities;

void bootstrap() {
    auto config = make_shared<Config>();
    config->width = 500;
    config->height = 500;
    config->fps = 15;
    config->useFixedTimeStep = true;
    config->glMajorVersion = 2;
    config->glMinorVersion = 0;
    IOCContainer::instance().register_type<Config>(config);
    IOCContainer::instance().register_type<IGameLoopCallback>(make_shared<Game>());
    IOCContainer::instance().register_type<IRenderer>(make_shared<SpriteRenderer>());
}