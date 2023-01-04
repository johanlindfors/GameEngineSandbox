#include "physics/ObjectCollider.h"
#include "utilities/MathHelper.h"

using namespace Utilities;

// Reference: https://www.jeffreythompson.org/collision-detection/circle-rect.php
bool ObjectCollider::intersects(Circle circle, Utilities::Rectangle rect)
{
	float testX = circle.position.x;
	float testY = circle.position.y;

	// which edge is closest?
	if (circle.position.x < rect.position.x)
		testX = rect.position.x;      						// test left edge
	else if (circle.position.x > rect.position.x + rect.width)
		testX = rect.position.x + rect.width;   // right edge
	if (circle.position.y < rect.position.y)
		testY = rect.position.y;      						// top edge
	else if (circle.position.y > rect.position.y + rect.height)
		testY = rect.position.y + rect.height; // bottom edge

	// get distance from closest edges
	float distX = circle.position.y - testX;
	float distY = circle.position.y - testY;
	float distance = sqrt( (distX*distX) + (distY*distY) );

	// if the distance is less than the radius, collision!
	if (distance <= circle.radius) {
		return true;
	}
	return false;
}

bool ObjectCollider::intersects(Utilities::Rectangle r1, Utilities::Rectangle r2)
{
	return r1.position.x <= (r2.position.x + r2.width) && (r1.position.x + r1.width) >= r2.position.x &&
		   r1.position.y <= (r2.position.y + r2.height) && (r1.position.y + r1.height) >= r2.position.y;
}
