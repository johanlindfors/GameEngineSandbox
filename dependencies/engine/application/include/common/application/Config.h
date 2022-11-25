#pragma once
#include <string>

namespace Engine
{
    struct Config 
    {
        int FPS = 60;
        int Width = 288;
        int Height = 505;
        std::string Title = "";
    };
}
