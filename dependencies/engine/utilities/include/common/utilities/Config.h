#pragma once
#include <string>

namespace Utilities
{
    struct Config 
    {
        int FPS = 60;
        bool UseFixedTimeStamp = false;
        int Width = 288;
        int Height = 505;
        std::string Title = "";
    };
}
