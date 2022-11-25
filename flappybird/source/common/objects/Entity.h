#pragma once
#include <memory>

namespace Utilities
{
	struct Vector2;
	class IStepTimer;
}

namespace Engine
{
	struct Sprite;
	struct Texture2D;
}

class Entity {
public:
	Entity(Utilities::Vector2 position);
	void SetTexture(Engine::Texture2D texture);
	void Update(std::shared_ptr<Utilities::IStepTimer> timer);
	std::shared_ptr<Engine::Sprite> GetSprite() const { return mSprite; }

protected:
	std::shared_ptr<Engine::Sprite> mSprite;
	int mScreenWidth;
	int mScreenHeight;
};
