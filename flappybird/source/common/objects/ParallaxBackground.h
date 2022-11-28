#pragma once
#include <memory>

class Clouds;
class Ground;
class Trees;
class Skyline;

namespace Engine
{
	class ISpriteRenderer;
	struct Sprite;
}

namespace Utilities
{
	class IStepTimer;
}

class ParallaxBackground
{
public:
    ParallaxBackground();
    ~ParallaxBackground();

	void Update(std::shared_ptr<Utilities::IStepTimer> timer);
	void Draw(std::shared_ptr<Engine::ISpriteRenderer> timer);

private:
	std::shared_ptr<Engine::Sprite> mBackground;
	std::unique_ptr<Clouds> mClouds;
	std::unique_ptr<Trees> mTrees;
	std::unique_ptr<Skyline> mSkyline;
	std::unique_ptr<Ground> mGround;
};
