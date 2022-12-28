#include "physics/ObjectCollider.h"
#include "utilities/MathHelper.h"

using namespace Utilities;

// Reference: https://www.jeffreythompson.org/collision-detection/circle-rect.php
bool ObjectCollider::Intersects(Circle circle, Utilities::Rectangle rect)
{
	float testX = circle.Position.X;
	float testY = circle.Position.Y;

	// which edge is closest?
	if (circle.Position.X < rect.Position.X)
		testX = rect.Position.X;      						// test left edge
	else if (circle.Position.X > rect.Position.X + rect.Width)
		testX = rect.Position.X + rect.Width;   // right edge
	if (circle.Position.Y < rect.Position.Y)
		testY = rect.Position.Y;      						// top edge
	else if (circle.Position.Y > rect.Position.Y + rect.Height)
		testY = rect.Position.Y + rect.Height; // bottom edge

	// get distance from closest edges
	float distX = circle.Position.X - testX;
	float distY = circle.Position.Y - testY;
	float distance = sqrt( (distX*distX) + (distY*distY) );

	// if the distance is less than the radius, collision!
	if (distance <= circle.Radius) {
		return true;
	}
	return false;
}

bool ObjectCollider::Intersects(Utilities::Rectangle r1, Utilities::Rectangle r2)
{
	return r1.Position.X <= (r2.Position.X + r2.Width) && (r1.Position.X + r1.Width) >= r2.Position.X &&
		   r1.Position.Y <= (r2.Position.Y + r2.Height) && (r1.Position.Y + r1.Height) >= r2.Position.Y;
}
