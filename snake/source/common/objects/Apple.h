#pragma once
#include "Entity.h"
#include "utilities/MathHelper.h"

namespace Engine 
{
	class ISpriteRenderer;
}

class Snake;
class PointCollider;

class Apple : public Entity {
public:
	Apple(Utilities::Point<int> position);
	void Draw(std::shared_ptr<Engine::ISpriteRenderer> renderer);
	void Update(int screenWidth, int screenHeight);
	void Reset(std::shared_ptr<Snake> snake, std::shared_ptr<PointCollider> collider);

private:
	float mScreenPositionX;
	float mScreenPositionY;
};
