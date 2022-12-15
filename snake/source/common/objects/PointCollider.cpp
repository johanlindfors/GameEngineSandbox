#include "PointCollider.h"

using namespace Utilities;

bool PointCollider::Collides(Point<int> point1, Point<int> point2)
{
    return ( point1.X == point2.X && point1.Y == point2.Y);
}