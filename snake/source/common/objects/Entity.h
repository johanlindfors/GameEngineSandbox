#pragma once
#include <memory>

namespace Utilities
{
	struct Point;
}

namespace Engine
{
	struct Sprite;
	struct Texture2D;
}

class Entity {
public:
	Entity(Utilities::Point position);
	void SetTexture(Engine::Texture2D texture) ;
	void Update(int screenWidth, int screenHeight);
	std::shared_ptr<Engine::Sprite> GetSprite() const { return mSprite; }

protected:
	std::shared_ptr<Engine::Sprite> mSprite;
	int mScreenWidth;
	int mScreenHeight;
};
