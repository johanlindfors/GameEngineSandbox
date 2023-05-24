#pragma once
#include "IObjectCollider.h"

namespace Utilities 
{
    class ObjectCollider : public Utilities::IObjectCollider {
    public:
        bool intersects(Utilities::Circle circle, Utilities::Rectangle<float> rectangle);
        bool intersects(Utilities::Rectangle<float> r1, Utilities::Rectangle<float> r2);
    };
}
