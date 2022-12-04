#pragma once
#include "Entity.h"
#include <list>
#include "MathHelper.h"
#include "physics/IPhysicsBody.h"

namespace Utilities
{
	class IStepTimer;	
}

namespace Engine
{
	class IInputManager;
	class ISpriteRenderer;
}

class IGameStateCallback;

class Bird : public Entity, public Engine::IPhysicsBody {
public:
	Bird(Utilities::Vector2 position);
	void Update(std::shared_ptr<Utilities::IStepTimer> timer);
	void Draw(std::shared_ptr<Engine::ISpriteRenderer> renderer);
	void Flap();
	Utilities::Circle Bounds;
	Utilities::Rectangle AABB;

private:
	void Reset();
	int mAnimationCounter;
	int mFramesPerAnimation;
#ifdef _DEBUG
	std::shared_ptr<Engine::Sprite> mDebugSprite;
#endif
};