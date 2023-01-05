#pragma once
#include "utilities/IOC.hpp"
#include "game/GameStateMachine.h"
#include "utilities/Config.h"
#include "game/GameDefines.h"
#include "physics/PhysicsEngine.h"
#include "physics/ObjectCollider.h"
#include "renderers/SpriteSheetRenderer.h"
#include "renderers/FontRenderer.h"
#include "systems/ScoreSystem.h"

#include "utilities/TweenEngine.h"
#include "systems/TweenyEngine.h"
#include <string>
#include <vector>

using namespace std;
using namespace Engine;
using namespace Utilities;

void bootstrap() {
    auto config = make_shared<Config>();
    config->fps = 60;
    config->useFixedTimeStep = true;
    config->width = SCREEN_WIDTH;
    config->height = SCREEN_HEIGHT;
    config->title = "Flappy Bird";
    config->glMajorVersion = 3;
    config->glMinorVersion = 2;
    IOCContainer::instance().register_type<Config>(config);

    IOCContainer::instance().register_type<IPhysicsEngine>(make_shared<PhysicsEngine>());
    IOCContainer::instance().register_type<IObjectCollider>(make_shared<ObjectCollider>());
    IOCContainer::instance().register_type<ITweenEngine>(make_shared<TweenyEngine>());
    
    auto spriteSheetRenderer = make_shared<SpriteSheetRenderer>(string("textures/atlas.txt"));    
    IOCContainer::instance().register_type<IRenderer>(spriteSheetRenderer);
    
    auto fontRenderer = make_shared<FontRenderer>(string("textures/numbers.fnt"));
    IOCContainer::instance().register_type<FontRenderer>(fontRenderer);

    auto scoreSystem = make_shared<ScoreSystem>();
    IOCContainer::instance().register_type<ScoreSystem>(scoreSystem);

    auto lazyLoaded = make_shared<LazyInitializedTypes>();
    lazyLoaded->emplace_back(spriteSheetRenderer);
    lazyLoaded->emplace_back(fontRenderer);
    lazyLoaded->emplace_back(scoreSystem);
    IOCContainer::instance().register_type<LazyInitializedTypes>(lazyLoaded);
    IOCContainer::instance().register_type<IGameLoopCallback>(make_shared<GameStateMachine>());
}