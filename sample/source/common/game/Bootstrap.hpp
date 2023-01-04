#pragma once
#include <string>
#include <vector>

#include "utilities/IOC.hpp"
#include "utilities/Config.h"
#include "Game.h"
#include "GameDefines.h"
#include "renderers/SimpleRenderer.h"
#include "resources/ResourceManager.h"
#include "filesystem/FileSystem.h"

using namespace std;
using namespace Engine;
using namespace Utilities;

void Bootstrap() {
    auto config = make_shared<Config>();
    config->FPS = 2;
    config->UseFixedTimeStep = false;
    config->Width = SCREEN_WIDTH;
    config->Height = SCREEN_HEIGHT;
    config->Title = "Sample 3d Scene";
    config->GLMajorVersion = 3;
    config->GLMinorVersion = 2;
    
    IOCContainer::Instance().Register<Config>(config);
    IOCContainer::Instance().Register<IGameLoopCallback>(make_shared<Sample::Game>());
}