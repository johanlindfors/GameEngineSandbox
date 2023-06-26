#pragma once
#include "physics/ICollidable.hpp"
#include "physics/IPhysicsBody.hpp"
#include "sprites/Sprite.hpp"
#include "game/GameDefines.hpp"
#include <memory>

namespace Utilities
{
	class IStepTimer;	
}

namespace Engine
{
	class IInputManager;
	class IRenderer;
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
		size = { 52.0f, 25.0f };
		position = Utilities::Point<float>{position.x, position.y};
	}
};

class Pipes
{
public:
	Pipes(Utilities::Point<float> position);
	void update(std::shared_ptr<Utilities::IStepTimer> timer);
	void draw(std::shared_ptr<Engine::IRenderer> renderer);
	bool isAlive;
	void reset(Utilities::Point<float> position);
	bool intersects(Utilities::Circle circle, Utilities::Rectangle<float> rect);
	bool intersects(Utilities::Rectangle<float> r1, Utilities::Rectangle<float> r2);

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
 