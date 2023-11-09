#pragma once
#include "utilities/MathHelper.hpp"

namespace Utilities
{
    class IObjectCollider
    {
    public:
        virtual bool intersects(Utilities::Circle circle, Utilities::Rectangle<float> rectangle) = 0;
        virtual bool intersects(Utilities::Rectangle<float> r1, Utilities::Rectangle<float> r2) = 0;
    };
}
