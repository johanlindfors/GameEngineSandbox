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

void Bootstrap() {
    auto config = make_shared<Config>();
    config->FPS = 60;
    config->UseFixedTimeStep = true;
    config->Width = SCREEN_WIDTH;
    config->Height = SCREEN_HEIGHT;
    config->Title = "Flappy Bird";
    config->GLMajorVersion = 3;
    config->GLMinorVersion = 2;
    IOCContainer::Instance().Register<Config>(config);

    IOCContainer::Instance().Register<IPhysicsEngine>(make_shared<PhysicsEngine>());
    IOCContainer::Instance().Register<IObjectCollider>(make_shared<ObjectCollider>());
    IOCContainer::Instance().Register<ITweenEngine>(make_shared<TweenyEngine>());
    
    auto spriteSheetRenderer = make_shared<SpriteSheetRenderer>(string("textures/atlas.txt"));    
    IOCContainer::Instance().Register<IRenderer>(spriteSheetRenderer);
    
    auto fontRenderer = make_shared<FontRenderer>(string("textures/numbers.fnt"));
    IOCContainer::Instance().Register<FontRenderer>(fontRenderer);

    auto scoreSystem = make_shared<ScoreSystem>();
    IOCContainer::Instance().Register<ScoreSystem>(scoreSystem);

    auto lazyLoaded = make_shared<LazyInitializedTypes>();
    lazyLoaded->emplace_back(spriteSheetRenderer);
    lazyLoaded->emplace_back(fontRenderer);
    lazyLoaded->emplace_back(scoreSystem);
    IOCContainer::Instance().Register<LazyInitializedTypes>(lazyLoaded);
    IOCContainer::Instance().Register<IGameLoopCallback>(make_shared<GameStateMachine>());
}