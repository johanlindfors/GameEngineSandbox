#pragma once
#include <string>
#include "glwrapper.h"

struct Texture2D {
public:
	std::wstring Name;
    float Width;
    float Height;
    GLuint TextureIndex;
};
