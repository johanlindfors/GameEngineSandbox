#pragma once
#include <string>
#include "glwrapper.h"

namespace Engine {
    struct Texture2D {
    public:
        std::wstring Name;
        float Width;
        float Height;
        GLuint TextureIndex;
    };
}
