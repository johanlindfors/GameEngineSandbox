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
	bool checkCollision(int x, int y);
	void update(int screenWidth, int screenHeight, IGameStateCallback* gameCallback);
	void handleInput(std::shared_ptr<Engine::IInputManager> input);
	void draw(std::shared_ptr<Engine::ISpriteRenderer> renderer);
	void increaseLength();

private:
	int mTail;
	std::list<Utilities::Point<int>> mTrail;
	void reset();

	friend class Apple;
};