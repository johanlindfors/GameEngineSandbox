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
	class ISpriteRenderer;
	class Sprite;
}

class IGameStateCallback;

class Bird : public Engine::IPhysicsBody {
public:
	Bird(Utilities::Point<float> position);
	void Update(std::shared_ptr<Utilities::IStepTimer> timer);
	void Draw(std::shared_ptr<Engine::ISpriteRenderer> renderer);
	void Flap();
	Utilities::Circle Bounds;
	Utilities::Rectangle AABB;
	bool IsKilled;
	void CollideWithPipe();
	void Reset();
	
private:
	int mAnimationCounter;
	int mFramesPerAnimation;
	std::shared_ptr<Engine::Sprite> mSprite;
#if defined(_DEBUG) && (DEBUG_TEXTURES_ENABLED == true)
	std::shared_ptr<Engine::Sprite> mDebugSprite;
#endif
};