#pragma once
#include "physics/ICollidable.hpp"
#include "physics/IPhysicsBody.hpp"
#include "sprites/Sprite.hpp"
#include "game/GameDefines.hpp"
#include <memory>

namespace Engine
{
	class IStepTimer;
}

namespace Engine
{
	class IInputManager;
	class IRenderer;
}

class Pipe
	: public Engine::Sprite,
	  public Engine::IPhysicsBody,
	  public Engine::ICollidable
{
public:
	using Engine::IPhysicsBody::position;

	Pipe(Engine::Point<float> position)
		: Sprite::Sprite(), IPhysicsBody::IPhysicsBody(position), ICollidable::ICollidable(position)
	{
		size = {52.0f, 25.0f};
		position = Engine::Point<float>{position.x, position.y};
	}
};

class Pipes
{
public:
	Pipes(Engine::Point<float> position);
	void update(std::shared_ptr<Engine::IStepTimer> timer);
	void draw(std::shared_ptr<Engine::IRenderer> renderer);
	bool isAlive;
	void reset(Engine::Point<float> position);
	bool intersects(Engine::Circle circle, Engine::Rectangle<float> rect);
	bool intersects(Engine::Rectangle<float> r1, Engine::Rectangle<float> r2);

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
