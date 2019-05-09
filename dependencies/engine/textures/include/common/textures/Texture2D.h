#pragma once
#include <string>
#include "glwrapper.h"

namespace Engine {
    struct Texture2D {
        std::wstring Name;
        int Width = 0;
        int Height = 0;
        int TextureIndex = 0;
		bool IsLoaded = false;
    };
}
