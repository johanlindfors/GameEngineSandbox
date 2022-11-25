#pragma once
#include "Entity.h"
#include <list>

namespace Utilities
{
	struct Vector2;
	class IStepTimer;	
}

namespace Engine
{
	class IInputManager;
	class ISpriteRenderer;
}

class IGameStateCallback;

class Bird : public Entity {
public:
	Bird(Utilities::Vector2 position);
	void Update(std::shared_ptr<Utilities::IStepTimer> timer);
	void HandleInput(std::shared_ptr<Engine::IInputManager> input);
	void Draw(std::shared_ptr<Engine::ISpriteRenderer> renderer);

private:
	void Reset();
};