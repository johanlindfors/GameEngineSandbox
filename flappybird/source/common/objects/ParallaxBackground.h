#pragma once
#include <memory>
#include "utilities/MathHelper.h"

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

private:
	std::unique_ptr<Clouds> mClouds;
	std::unique_ptr<Trees> mTrees;
	std::unique_ptr<Skyline> mSkyline;
    bool mIsRunning;
};
