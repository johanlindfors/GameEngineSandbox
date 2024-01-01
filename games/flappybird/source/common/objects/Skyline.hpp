#pragma once
#include <list>
#include "utilities/MathHelper.hpp"
#include <vector>
#include "utilities/MathHelper.hpp"

namespace Engine
{
	class IStepTimer;
}

namespace Engine
{
	class IRenderer;
	struct Sprite;
}

class Skyline
{
public:
	Skyline(Engine::Point<float> position, Engine::Vector2 velocity);
	void update(std::shared_ptr<Engine::IStepTimer> timer);
	void draw(std::shared_ptr<Engine::IRenderer> renderer);
	void initializeSprite();

private:
	std::shared_ptr<Engine::Sprite> mSprite;
	std::vector<Engine::Point<float>> mSkyline;
	Engine::Vector2 mVelocity;
	int mTextureOffset;
};