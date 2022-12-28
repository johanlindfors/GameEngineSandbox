#pragma once
#include <string>

namespace Engine {
    struct Texture2D {
        std::string Name;
        int Width = 0;
        int Height = 0;
        int TextureIndex = 0;
		bool IsLoaded = false;
    };
}
