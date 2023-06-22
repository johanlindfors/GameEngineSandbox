#pragma once
#include <memory>
#include "utilities/MathHelper.hpp"

namespace Engine
{
	struct Sprite;
	struct Texture2D;
}

class Entity {
public:
	Entity(Utilities::Point<int> position);
	void setTexture(Engine::Texture2D texture) ;
	void update(int screenWidth, int screenHeight);
	std::shared_ptr<Engine::Sprite> getSprite() const { return mSprite; }

protected:
	std::shared_ptr<Engine::Sprite> mSprite;
	int mScreenWidth;
	int mScreenHeight;
};
