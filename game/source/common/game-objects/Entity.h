#pragma once
#include <memory>

namespace Utilities
{
	struct Vector2;
}

namespace Engine
{
	struct Sprite;
	struct Texture2D;
}

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
