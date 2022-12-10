#pragma once
#include "utilities/IOC.hpp"
#include "game/GameStateMachine.h"
#include "utilities/Config.h"
#include "game/GameDefines.h"
#include "physics/PhysicsEngine.h"
#include "physics/ObjectCollider.h"
#include "renderer/SpriteSheetRenderer.h"

#include "utilities/TweenEngine.h"
#include "systems/TweenyEngine.h"
#include <string>

using namespace std;
using namespace Engine;
using namespace Utilities;

void Bootstrap() {
    auto config = make_shared<Config>();
    config->FPS = 60;
    config->UseFixedTimeStamp = false;
    config->Width = SCREEN_WIDTH;
    config->Height = SCREEN_HEIGHT;
    config->Title = "Flappy Bird";
    IOCContainer::Instance().Register<IPhysicsEngine>(make_shared<PhysicsEngine>());
    IOCContainer::Instance().Register<IObjectCollider>(make_shared<ObjectCollider>());
    IOCContainer::Instance().Register<ITweenEngine>(make_shared<TweenyEngine>());
    IOCContainer::Instance().Register<ISpriteRenderer>(make_shared<SpriteSheetRenderer>(wstring(L"atlas")));

    IOCContainer::Instance().Register<Config>(config);
    IOCContainer::Instance().Register<IGameLoopCallback>(make_shared<GameStateMachine>());
}