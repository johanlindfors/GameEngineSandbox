#pragma once
#include <memory>
#include "MathHelper.h"
#include "Ground.h"

class Clouds;
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

    void Pause() { mIsRunning = false; }
    void Resume() { mIsRunning = true; }

	Utilities::Rectangle GetGroundAABB() { return mGround->AABB; }

private:
	std::unique_ptr<Clouds> mClouds;
	std::unique_ptr<Trees> mTrees;
	std::unique_ptr<Skyline> mSkyline;
	std::shared_ptr<Ground> mGround;
    bool mIsRunning;
};
