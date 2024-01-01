#include "physics/ObjectCollider.hpp"
#include "utilities/MathHelper.hpp"

using namespace Engine;

// Reference: https://www.jeffreythompson.org/collision-detection/circle-rect.php
bool ObjectCollider::intersects(Circle circle, Engine::Rectangle<float> rect)
{
	float testX = circle.position.x;
	float testY = circle.position.y;

	// which edge is closest?
	if (circle.position.x < rect.position.x)
		testX = rect.position.x; // test left edge
	else if (circle.position.x > rect.position.x + rect.size.width)
		testX = rect.position.x + rect.size.width; // right edge
	if (circle.position.y < rect.position.y)
		testY = rect.position.y; // top edge
	else if (circle.position.y > rect.position.y + rect.size.height)
		testY = rect.position.y + rect.size.height; // bottom edge

	// get distance from closest edges
	float distX = circle.position.x - testX;
	float distY = circle.position.y - testY;
	float distance = static_cast<float>(sqrt((distX * distX) + (distY * distY)));

	// if the distance is less than the radius, collision!
	if (distance <= circle.radius)
	{
		return true;
	}
	return false;
}

bool ObjectCollider::intersects(Engine::Rectangle<float> r1, Engine::Rectangle<float> r2)
{
	return r1.position.x <= (r2.position.x + r2.size.width) && (r1.position.x + r1.size.width) >= r2.position.x &&
		   r1.position.y <= (r2.position.y + r2.size.height) && (r1.position.y + r1.size.height) >= r2.position.y;
}
