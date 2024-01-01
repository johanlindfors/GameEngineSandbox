#pragma once
#include <list>
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

class Clouds
{
public:
	Clouds(Engine::Point<float> position, Engine::Vector2 velocity);
	void update(std::shared_ptr<Engine::IStepTimer> timer);
	void draw(std::shared_ptr<Engine::IRenderer> renderer);
	void initializeSprite();

private:
	std::shared_ptr<Engine::Sprite> mClouds;
	std::shared_ptr<Engine::Sprite> mCloudsBackground;
	Engine::Vector2 mVelocity;
	Engine::Point<float> mPosition;
	int mCloudsOffset;
	int mCloudsBackgroundOffset;
};