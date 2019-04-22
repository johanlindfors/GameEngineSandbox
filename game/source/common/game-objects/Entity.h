#pragma once
#include "MathHelper.h"
#include "sprites/Sprite.h"
#include "game_defines.h"

class Entity {
public:
	Entity(Utilities::Vector2 position);
	void SetTexture(Engine::Texture2D texture) ;
	void Update(int screenWidth, int screenHeight);

protected:
	Engine::Sprite mSprite;
};
