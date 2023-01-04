#pragma once
#include "IObjectCollider.h"

namespace Utilities 
{
    class ObjectCollider : public Utilities::IObjectCollider {
    public:
        bool intersects(Utilities::Circle circle, Utilities::Rectangle rectangle);
        bool intersects(Utilities::Rectangle r1, Utilities::Rectangle r2);
    };
}
