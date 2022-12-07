#pragma once
#include <list>
#include "utilities/MathHelper.h"
#include <vector>
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

class Skyline {
public:
	Skyline(Utilities::Point<float> position, Utilities::Vector2 velocity);
	void Update(std::shared_ptr<Utilities::IStepTimer> timer);
	void Draw(std::shared_ptr<Engine::ISpriteRenderer> renderer);

private:
	std::shared_ptr<Engine::Sprite> mSprite;
	std::vector<Utilities::Point<float>> mSkyline;
	Utilities::Vector2 mVelocity;
	int mTextureOffset;
};