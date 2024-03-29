#pragma once
#include <list>
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

class Trees
{
public:
	Trees(Utilities::Point<float> position, Utilities::Vector2 velocity);
	void update(std::shared_ptr<Utilities::IStepTimer> timer);
	void draw(std::shared_ptr<Engine::IRenderer> renderer);
	void initializeSprite();

private:
	std::shared_ptr<Engine::Sprite> mTrees;
	std::shared_ptr<Engine::Sprite> mTreesBackground;
	Utilities::Vector2 mVelocity;
	Utilities::Point<float> mPosition;
	int mCloudsOffset;
	int mCloudsBackgroundOffset;
};
