#pragma once
#include "IObjectCollider.h"

namespace Utilities 
{
    class ObjectCollider : public Utilities::IObjectCollider {
    public:
        bool Intersects(Utilities::Circle circle, Utilities::Rectangle rectangle);
        bool Intersects(Utilities::Rectangle r1, Utilities::Rectangle r2);
    };
}
