#pragma once
#include "utilities/IOC.hpp"
#include "game/Game.h"
#include "utilities/Config.h"
#include "renderers/SpriteRenderer.h"

using namespace std;
using namespace Engine;
using namespace Utilities;

void Bootstrap() {
    auto config = make_shared<Config>();
    config->Width = 500;
    config->Height = 500;
    config->FPS = 15;
    config->UseFixedTimeStamp = true;
    IOCContainer::Instance().Register<Config>(config);
    IOCContainer::Instance().Register<IGameLoopCallback>(make_shared<Game>());
    IOCContainer::Instance().Register<ISpriteRenderer>(make_shared<SpriteRenderer>());
}