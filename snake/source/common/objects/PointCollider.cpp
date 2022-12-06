#include "PointCollider.h"
#include "utilities/MathHelper.h"

using Utilities::Point;

bool PointCollider::Collides(Point point1, Point point2)
{
    return ( point1.X == point2.X && point1.Y == point2.Y);
}