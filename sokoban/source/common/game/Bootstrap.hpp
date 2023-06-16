#pragma once
#include "utilities/IOC.hpp"
#include "game/GameStateMachine.hpp"
#include "utilities/Config.hpp"
#include "game/GameDefines.hpp"
#include "renderers/FontRenderer.hpp"

#include "utilities/TweenEngine.hpp"
#include <string>
#include <vector>
#include "utilities/TweenEngine.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;

void bootstrap() {
    auto config = make_shared<Config>();
    config->fps = 60;
    config->useFixedTimeStep = true;
    config->width = SCREEN_WIDTH;
    config->height = SCREEN_HEIGHT;
    config->title = "Sokoban";
    config->glMajorVersion = 3;
    config->glMinorVersion = 3;
    IOCContainer::instance().register_type<Config>(config);

    IOCContainer::instance().register_type<ITweenEngine>(make_shared<TweenEngine>());
    IOCContainer::instance().register_type<IGameLoopCallback>(make_shared<GameStateMachine>());
    IOCContainer::instance().register_type<ITweenEngine>(make_shared<TweenEngine>());
}