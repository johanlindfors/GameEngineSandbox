#pragma once
#include "Entity.hpp"
#include <list>
#include "utilities/MathHelper.hpp"

namespace Engine
{
	class IInputManager;
	class SpriteRenderer;
}

struct BodyPart {
	Utilities::Point<int> position;
	Utilities::Point<int> direction;
};

class Tail {

};

class IGameStateCallback;
class Apple;

class Snake : public Entity {
public:
	Snake(Utilities::Point<int> position);
	bool checkCollision(int x, int y);
	void update(int screenWidth, int screenHeight, IGameStateCallback* gameCallback);
	void handleInput(std::shared_ptr<Engine::IInputManager> input);
	void draw(std::shared_ptr<Engine::SpriteRenderer> renderer);
	void increaseLength();
	Utilities::Point<int> getHeadPosition() { return mHead.position; }

private:
	BodyPart mHead;
	std::list<BodyPart> mBody;
	BodyPart mTail;
	int mBodyLength;

	void reset();

	friend class Apple;
};
