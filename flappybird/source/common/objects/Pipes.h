#pragma once
#include "physics/ICollidable.h"
#include "physics/IPhysicsBody.h"
#include "renderers/Sprite.h"
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
	using Engine::IPhysicsBody::position;

	Pipe(Utilities::Point<float> position)
		: Sprite::Sprite()
		, IPhysicsBody::IPhysicsBody(position) 
		, ICollidable::ICollidable(position)
	{
		width = 52,
		height = 25;
		position = Utilities::Point<float>{position.x, position.y};
	}
};

class Pipes
{
public:
	Pipes(Utilities::Point<float> position);
	void update(std::shared_ptr<Utilities::IStepTimer> timer);
	void draw(std::shared_ptr<Engine::ISpriteRenderer> renderer);
	bool isAlive;
	void reset(Utilities::Point<float> position);
	bool intersects(Utilities::Circle circle, Utilities::Rectangle rect);
	bool intersects(Utilities::Rectangle r1, Utilities::Rectangle r2);

	std::shared_ptr<Pipe> topPipe;
	std::shared_ptr<Pipe> bottomPipe;
	std::shared_ptr<Engine::Sprite> topPipeSprite;
	std::shared_ptr<Engine::Sprite> bottomPipeSprite;
	bool hasScored;
#if defined(_DEBUG) && (DEBUG_TEXTURES_ENABLED == true)
	std::shared_ptr<Engine::Sprite> topPipeDebugSprite;
	std::shared_ptr<Engine::Sprite> bottomPipeDebugSprite;	
#endif
};
 