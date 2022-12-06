#pragma once
#include "Entity.h"
#include <list>
#include "utilities/MathHelper.h"
#include <vector>

namespace Utilities
{
	class IStepTimer;	
}

namespace Engine
{
	class ISpriteRenderer;
	class Sprite;
}

class Skyline {
public:
	Skyline(Utilities::Point position, Utilities::Vector2 velocity);
	void Update(std::shared_ptr<Utilities::IStepTimer> timer);
	void Draw(std::shared_ptr<Engine::ISpriteRenderer> renderer);

private:
	std::vector<std::shared_ptr<Engine::Sprite>> mSkyline;
	Utilities::Vector2 mVelocity;
	Utilities::Point mPosition;
	int mTextureOffset;
};