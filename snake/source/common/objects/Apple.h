#pragma once
#include "Entity.h"

namespace Engine 
{
	class ISpriteRenderer;
}

namespace Utilities 
{
	struct Vector2;
}

class Snake;
class VectorCollider;

class Apple : public Entity {
public:
	Apple(Utilities::Vector2 position);
	void Draw(std::shared_ptr<Engine::ISpriteRenderer> renderer);
	void Update(int screenWidth, int screenHeight);
	void Reset(std::shared_ptr<Snake> snake, std::shared_ptr<VectorCollider> collider);

private:
	float mScreenPositionX;
	float mScreenPositionY;
};
