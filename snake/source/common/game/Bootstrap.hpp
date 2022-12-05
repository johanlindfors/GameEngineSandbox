#pragma once
#include "IOC.hpp"
#include "game/Game.h"
#include "application/Config.h"

using namespace std;
using namespace Engine;
using namespace Utilities;

void Bootstrap() {
    auto config = make_shared<Config>();
    config->Width = 500;
    config->Height = 500;
    config->FPS = 15;
    IOCContainer::Instance().Register<Config>(config);
    IOCContainer::Instance().Register<IGameLoopCallback>(make_shared<Game>());
}