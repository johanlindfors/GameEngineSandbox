#pragma once
#include <list>
#include "utilities/MathHelper.hpp"
#include <vector>
#include "utilities/MathHelper.hpp"

namespace Utilities
{
	class IStepTimer;	
}

namespace Engine
{
	class IRenderer;
	struct Sprite;
}

class Skyline {
public:
	Skyline(Utilities::Point<float> position, Utilities::Vector2 velocity);
	void update(std::shared_ptr<Utilities::IStepTimer> timer);
	void draw(std::shared_ptr<Engine::IRenderer> renderer);
	void initializeSprite();
	
private:
	std::shared_ptr<Engine::Sprite> mSprite;
	std::vector<Utilities::Point<float>> mSkyline;
	Utilities::Vector2 mVelocity;
	int mTextureOffset;
};