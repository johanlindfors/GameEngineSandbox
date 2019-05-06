#pragma once
#include <memory>

namespace Utilities
{
    struct Vector2;
}

class VectorCollider {
public:
    bool Collides(Utilities::Vector2 vector1, Utilities::Vector2 vector2) const;
};
