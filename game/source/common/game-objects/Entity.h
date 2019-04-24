#pragma once
#include "MathHelper.h"
#include "sprites/Sprite.h"
#include "GameDefines.h"
#include <memory>

class Entity {
public:
	Entity(Utilities::Vector2 position);
	void SetTexture(Engine::Texture2D texture) ;
	void Update(int screenWidth, int screenHeight);
	std::shared_ptr<Engine::Sprite> GetSprite() { return mSprite; }

protected:
	std::shared_ptr<Engine::Sprite> mSprite;
	int mScreenWidth;
	int mScreenHeight;
};
