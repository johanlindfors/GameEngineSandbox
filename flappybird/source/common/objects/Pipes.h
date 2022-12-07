#pragma once
#include "physics/ICollidable.h"
#include "physics/IPhysicsBody.h"
#include "renderer/Sprite.h"
#include "game/GameDefines.h"
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
	using Engine::IPhysicsBody::Position;

	Pipe(Utilities::Point<float> position)
		: Sprite::Sprite()
		, IPhysicsBody::IPhysicsBody(position) 
		, ICollidable::ICollidable(position)
	{
		Width = 52,
		Height = 25;
		Position = Utilities::Point<float>(position.X, position.Y);
	}
};

class Pipes
{
public:
	Pipes(Utilities::Point<float> position);
	void Update(std::shared_ptr<Utilities::IStepTimer> timer);
	void Draw(std::shared_ptr<Engine::ISpriteRenderer> renderer);
	bool IsAlive;
	void Reset(Utilities::Point<float> position);
	bool Intersects(Utilities::Circle circle, Utilities::Rectangle rect);
	bool Intersects(Utilities::Rectangle r1, Utilities::Rectangle r2);

	std::shared_ptr<Pipe> TopPipe;
	std::shared_ptr<Pipe> BottomPipe;
	std::shared_ptr<Engine::Sprite> TopPipeSprite;
	std::shared_ptr<Engine::Sprite> BottomPipeSprite;
	bool TopSpriteCollided;
	bool BottomSpriteCollided;
#if defined(_DEBUG) && (DEBUG_TEXTURES_ENABLED == true)
	std::shared_ptr<Engine::Sprite> TopPipeDebugSprite;
	std::shared_ptr<Engine::Sprite> BottomPipeDebugSprite;	
#endif
};
 