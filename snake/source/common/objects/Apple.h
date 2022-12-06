#pragma once
#include "Entity.h"

namespace Engine 
{
	class ISpriteRenderer;
}

namespace Utilities 
{
	struct Point;
}

class Snake;
class PointCollider;

class Apple : public Entity {
public:
	Apple(Utilities::Point position);
	void Draw(std::shared_ptr<Engine::ISpriteRenderer> renderer);
	void Update(int screenWidth, int screenHeight);
	void Reset(std::shared_ptr<Snake> snake, std::shared_ptr<PointCollider> collider);

private:
	float mScreenPositionX;
	float mScreenPositionY;
};
