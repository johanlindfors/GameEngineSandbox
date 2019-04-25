#pragma once
#include <string>
#include "glwrapper.h"

namespace Engine {
    struct Texture2D {
        std::wstring Name;
        int Width;
        int Height;
        GLuint TextureIndex;
    };
}
