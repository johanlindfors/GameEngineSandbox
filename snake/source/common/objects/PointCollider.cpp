#include "PointCollider.hpp"

using namespace Utilities;

bool PointCollider::collides(Point<int> point1, Point<int> point2)
{
    return ( point1.x == point2.x && point1.y == point2.y);
}