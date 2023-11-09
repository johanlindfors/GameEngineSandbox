#pragma once
#include <string>

namespace Utilities
{
    struct Config
    {
        int fps = 60;
        bool useFixedTimeStep = false;
        int width = 288;
        int height = 505;
        std::string title = "";
        std::string executable = "";
        unsigned int glMajorVersion = 3;
        unsigned int glMinorVersion = 3;
    };
}
