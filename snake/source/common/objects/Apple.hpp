#pragma once
#include "Entity.hpp"
#include "utilities/MathHelper.hpp"

namespace Engine 
{
	class SpriteRenderer;
}

class Snake;
class PointCollider;

class Apple : public Entity {
public:
	Apple(Utilities::Point<int> position);
	void draw(std::shared_ptr<Engine::SpriteRenderer> renderer);
	void update(int screenWidth, int screenHeight);
	void reset(std::shared_ptr<Snake> snake, std::shared_ptr<PointCollider> collider);

private:
	float mScreenPositionX;
	float mScreenPositionY;
};
