#pragma once

namespace Utilities
{
    struct Vector2;
}

class VectorCollider {
public:
	static bool Collides(Utilities::Vector2 vector1, Utilities::Vector2 vector2);
};
