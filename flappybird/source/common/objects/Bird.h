#pragma once
#include <list>
#include "utilities/MathHelper.h"
#include "physics/IPhysicsBody.h"
#include <functional>
#include "utilities/IStepTimer.h"
#include <vector>
#include "game/GameDefines.h"

namespace Utilities
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

class Bird : public Engine::IPhysicsBody {
public:
	Bird(Utilities::Point<float> position);
	void update(std::shared_ptr<Utilities::IStepTimer> timer);
	void draw(std::shared_ptr<Engine::IRenderer> renderer);
	void flap();
	void initializeSprite();
	Utilities::Circle bounds;
	Utilities::Rectangle<float> AABB;
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