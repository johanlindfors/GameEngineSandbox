#include "physics/ObjectCollider.h"
#include "MathHelper.h"

using namespace Utilities;

// Reference: https://www.jeffreythompson.org/collision-detection/circle-rect.php
bool ObjectCollider::Intersects(Circle circle, Rectangle rect)
{
	float testX = circle.X;
	float testY = circle.Y;

	// which edge is closest?
	if (circle.X < rect.X) testX = rect.X;      						// test left edge
	else if (circle.X > rect.X+rect.Width) testX = rect.X+rect.Width;   // right edge
	if (circle.Y < rect.Y) testY = rect.Y;      						// top edge
	else if (circle.Y > rect.Y+rect.Height) testY = rect.Y+rect.Height; // bottom edge

	// get distance from closest edges
	float distX = circle.X-testX;
	float distY = circle.Y-testY;
	float distance = sqrt( (distX*distX) + (distY*distY) );

	// if the distance is less than the radius, collision!
	if (distance <= circle.Radius) {
		return true;
	}
	return false;
}

bool ObjectCollider::Intersects(Rectangle r1, Rectangle r2)
{
	return r1.X <= (r2.X + r2.Width) && (r1.X + r1.Width) >= r2.X &&
		   r1.Y <= (r2.Y + r2.Height) && (r1.Y + r1.Height) >= r2.Y;
}
