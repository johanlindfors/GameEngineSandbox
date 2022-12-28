#pragma once
#include "Entity.h"
#include <list>
#include "utilities/MathHelper.h"

namespace Engine
{
	class IInputManager;
	class ISpriteRenderer;
}

class IGameStateCallback;
class Apple;

class Snake : public Entity {
public:
	Snake(Utilities::Point<int> position);
	bool CheckCollision(int x, int y);
	void Update(int screenWidth, int screenHeight, IGameStateCallback* gameCallback);
	void HandleInput(std::shared_ptr<Engine::IInputManager> input);
	void Draw(std::shared_ptr<Engine::ISpriteRenderer> renderer);
	void IncreaseLength();

private:
	int mTail;
	std::list<Utilities::Point<int>> mTrail;
	void Reset();

	friend class Apple;
};