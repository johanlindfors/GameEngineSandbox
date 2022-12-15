#include "PointCollider.h"

using namespace Utilities;

bool PointCollider::Collides(Point<float> point1, Point<float> point2)
{
    return ( point1.X == point2.X && point1.Y == point2.Y);
}