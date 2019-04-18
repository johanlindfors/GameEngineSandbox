#pragma once
#include "textures/Texture2D.h"

class Sprite {
public:
    Sprite() 
		: mTexture({})
		, mPositionX(0.0f)
		, mPositionY(0.0f)
		, mVelocityX(0.0f)
		, mVelocityY(0.0f)
		, mWidth(0.0f)
		, mHeight(0.0f)
	{}
    ~Sprite() = default;
    Texture2D mTexture;
    float mPositionX;
    float mPositionY;
	float mVelocityX;
	float mVelocityY;
    float mWidth;
    float mHeight;
};