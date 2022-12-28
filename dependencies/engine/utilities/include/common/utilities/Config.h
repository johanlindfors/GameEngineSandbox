#pragma once
#include <string>

namespace Utilities
{
    struct Config 
    {
        int FPS = 60;
        bool UseFixedTimeStep = false;
        int Width = 288;
        int Height = 505;
        std::string Title = "";
    };
}
