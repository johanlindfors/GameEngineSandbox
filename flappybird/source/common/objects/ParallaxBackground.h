#pragma once
#include <memory>
#include "utilities/MathHelper.h"

class Clouds;
class Trees;
class Skyline;

namespace Engine
{
	class IRenderer;
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

	void update(std::shared_ptr<Utilities::IStepTimer> timer);
	void draw(std::shared_ptr<Engine::IRenderer> renderer);

    void pause() { mIsRunning = false; }
    void resume() { mIsRunning = true; }
	void initializeSprites();

private:
	std::unique_ptr<Clouds> mClouds;
	std::unique_ptr<Trees> mTrees;
	std::unique_ptr<Skyline> mSkyline;
    bool mIsRunning;
};
