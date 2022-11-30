#pragma once
#include "Entity.h"
#include <list>
#include "MathHelper.h"

namespace Utilities
{
	class IStepTimer;	
}

namespace Engine
{
	class IInputManager;
	class ISpriteRenderer;
}

class IPhysicsBody
{
public:
	IPhysicsBody()
		: IsAlive(true)
		, X(0)
		, Y(0)
		, Velocity(Utilities::Vector2(0.0f,0.0f))
		, AllowGravity(true) 
	{}

	virtual ~IPhysicsBody() = default;

	bool IsAlive;
	float X;
	float Y;
	Utilities::Vector2 Velocity;
    bool AllowGravity;
};

class IGameStateCallback;

class Bird : public Entity, public IPhysicsBody {
public:
	Bird(Utilities::Vector2 position);
	void Update(std::shared_ptr<Utilities::IStepTimer> timer);
	void HandleInput(std::shared_ptr<Engine::IInputManager> input);
	void Draw(std::shared_ptr<Engine::ISpriteRenderer> renderer);
	void Flap();
	
private:
	void Reset();
	int mAnimationCounter;
	int mFramesPerAnimation;
};