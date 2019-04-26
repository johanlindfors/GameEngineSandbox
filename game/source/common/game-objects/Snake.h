#pragma once
#include "Entity.h"
#include <list>

namespace Utilities
{
	struct Vector2;
}

namespace Engine
{
	class IInputManager;
	class ISpriteRenderer;
}

class IGameStateCallback;

class Snake : public Entity {
public:
	Snake(Utilities::Vector2 position);
	bool CheckCollision(int x, int y);
	void Update(int screenWidth, int screenHeight, IGameStateCallback* gameCallback);
	void HandleInput(std::shared_ptr<Engine::IInputManager> input);
	void Draw(std::shared_ptr<Engine::ISpriteRenderer> renderer);
	void IncreaseLength();

private:
	int mTail;
	std::list<Utilities::Vector2> mTrail;
	void Reset();
};