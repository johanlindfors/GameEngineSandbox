#pragma once

// stl
#include <string>
#include <vector>

// engine
#include "utilities/IOC.hpp"
#include "utilities/Config.hpp"
#include "renderers/FontRenderer.hpp"
#include "utilities/TweenEngine.hpp"
#if defined(USE_HTTP)
#include "http/HttpClient.hpp"
#endif
// game
#include "game/GameStateMachine.hpp"
#include "game/GameDefines.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;

void bootstrap()
{
    auto config = make_shared<Config>();
    config->fps = FRAMES_PER_SECOND;
    config->useFixedTimeStep = true;
    config->width = SCREEN_WIDTH;
    config->height = SCREEN_HEIGHT;
    config->title = "Sokoban";
    config->executable = "sokoban";
    config->glMajorVersion = 3;
    config->glMinorVersion = 3;
    IOCContainer::instance().register_type<Config>(config);

#if defined(USE_HTTP)
    IOCContainer::instance().register_type<IHttpClient>(make_shared<CprHttpClient>());
#endif
    IOCContainer::instance().register_type<IGameLoopCallback>(make_shared<GameStateMachine>());
    IOCContainer::instance().register_type<ITweenEngine>(make_shared<TweenEngine>());
}
