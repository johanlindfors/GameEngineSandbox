#pragma once
#include <string>

namespace Engine
{
    struct Texture2D
    {
        std::string name;
        int width = 0;
        int height = 0;
        unsigned int textureIndex = 0;
        bool isLoaded = false;
    };
}
