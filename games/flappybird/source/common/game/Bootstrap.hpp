#pragma once
#include "utilities/IOC.hpp"
#include "game/GameStateMachine.hpp"
#include "utilities/Config.hpp"
#include "game/GameDefines.hpp"
#include "physics/PhysicsEngine.hpp"
#include "physics/ObjectCollider.hpp"
#include "renderers/FontRenderer.hpp"
#include "systems/ScoreSystem.hpp"

#include "utilities/TweenEngine.hpp"
#include "systems/TweenyEngine.hpp"
#include <string>
#include <vector>

using namespace std;
using namespace Engine;
using namespace Utilities;

void bootstrap()
{
    auto config = make_shared<Config>();
    config->fps = 60;
    config->useFixedTimeStep = true;
    config->width = SCREEN_WIDTH;
    config->height = SCREEN_HEIGHT;
    config->title = "Flappy Bird";
    config->executable = "flappybird";
    config->glMajorVersion = 3;
    config->glMinorVersion = 3;
    IOCContainer::instance().register_type<Config>(config);

    IOCContainer::instance().register_type<IPhysicsEngine>(make_shared<PhysicsEngine>());
    IOCContainer::instance().register_type<IObjectCollider>(make_shared<ObjectCollider>());
    IOCContainer::instance().register_type<ITweenEngine>(make_shared<TweenEngine>());

    auto scoreSystem = make_shared<ScoreSystem>();
    IOCContainer::instance().register_type<ScoreSystem>(scoreSystem);

    IOCContainer::instance().register_type<IGameLoopCallback>(make_shared<GameStateMachine>());
}