#pragma once
#include "utilities/MathHelper.h"

class PointCollider {
public:
	static bool Collides(Utilities::Point<float> point1, Utilities::Point<float> point2);
};
