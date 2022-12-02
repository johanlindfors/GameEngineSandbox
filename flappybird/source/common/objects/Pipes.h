#pragma once
#include "physics/ICollidable.h"
#include "physics/IPhysicsBody.h"
#include "renderer/Sprite.h"
#include <memory>

namespace Utilities
{
	class IStepTimer;	
}

namespace Engine
{
	class IInputManager;
	class ISpriteRenderer;
}

class Pipe 
	: public Engine::Sprite
	, public Engine::IPhysicsBody
	, public Engine::ICollidable
{
public:
	Pipe(Utilities::Vector2 position)
		: Sprite::Sprite()
		, IPhysicsBody::IPhysicsBody(position) 
		, ICollidable::ICollidable(position)
	{
		Width = 52,
		Height = 25;
		Position = position;
	}
};

class Pipes
{
public:
	Pipes(Utilities::Vector2 position);
	void Update(std::shared_ptr<Utilities::IStepTimer> timer);
	void Draw(std::shared_ptr<Engine::ISpriteRenderer> renderer);
	bool IsAlive;
	void Reset(Utilities::Vector2 position);

	std::shared_ptr<Pipe> TopPipe;
	std::shared_ptr<Pipe> BottomPipe;
	std::shared_ptr<Engine::Sprite> TopPipeSprite;
	std::shared_ptr<Engine::Sprite> BottomPipeSprite;
};
 