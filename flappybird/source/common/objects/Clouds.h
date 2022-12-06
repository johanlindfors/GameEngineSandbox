#pragma once
#include <list>
#include "utilities/MathHelper.h"

namespace Utilities
{
	class IStepTimer;	
}

namespace Engine
{
	class ISpriteRenderer;
	class Sprite;
}

class Clouds {
public:
	Clouds(Utilities::Point position, Utilities::Vector2 velocity);
	void Update(std::shared_ptr<Utilities::IStepTimer> timer);
	void Draw(std::shared_ptr<Engine::ISpriteRenderer> renderer);

private:
	std::shared_ptr<Engine::Sprite> mClouds;
	std::shared_ptr<Engine::Sprite> mCloudsBackground;
	Utilities::Vector2 mVelocity;
	Utilities::Point mPosition;
	int mCloudsOffset;
	int mCloudsBackgroundOffset;
};