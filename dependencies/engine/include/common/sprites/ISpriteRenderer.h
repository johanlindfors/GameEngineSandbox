#pragma once
#include "Sprite.h"

class ISpriteRenderer {
public:
    virtual void UpdateWindowSize(GLsizei width, GLsizei height) = 0;
    virtual void DrawSprite(Sprite& texture) = 0;
};
