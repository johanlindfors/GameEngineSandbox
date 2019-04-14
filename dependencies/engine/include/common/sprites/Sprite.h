#pragma once
#include "textures/Texture2D.h"

class Sprite {
public:
    Sprite() = default;
    ~Sprite() = default;
    Texture2D mTexture;
    float mPositionX;
    float mPositionY;
    float mWidth;
    float mHeight;
};