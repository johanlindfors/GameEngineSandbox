#pragma once
#include <list>
#include "utilities/MathHelper.hpp"
#include "physics/IPhysicsBody.hpp"
#include <functional>
#include "utilities/IStepTimer.hpp"
#include <vector>
#include "game/GameDefines.hpp"

namespace Engine
{
	class IStepTimer;
}

namespace Engine
{
	class IInputManager;
	class IRenderer;
	struct Sprite;
}

class IGameStateCallback;

class Bird : public Engine::IPhysicsBody
{
public:
	Bird(Engine::Point<float> position);
	void update(std::shared_ptr<Engine::IStepTimer> timer);
	void draw(std::shared_ptr<Engine::IRenderer> renderer);
	void flap();
	void initializeSprite();
	Engine::Circle bounds;
	Engine::Rectangle<float> AABB;
	bool isKilled;
	void collideWithPipe();
	void reset();

private:
	int mCounter;
	int mAnimationCounter;
	int mFramesPerAnimation;
	std::shared_ptr<Engine::Sprite> mSprite;
#if defined(_DEBUG) && (DEBUG_TEXTURES_ENABLED == true)
	std::shared_ptr<Engine::Sprite> mDebugSprite;
#endif
};