#pragma once

namespace Utilities
{
    struct Point;
}

class PointCollider {
public:
	static bool Collides(Utilities::Point point1, Utilities::Point point2);
};
