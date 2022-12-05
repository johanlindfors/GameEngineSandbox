#pragma once

namespace Utilities
{
    struct Circle;
    struct Rectangle;

    class IObjectCollider {
    public:
        virtual bool Intersects(Utilities::Circle circle, Utilities::Rectangle rectangle) = 0;
        virtual bool Intersects(Utilities::Rectangle r1, Utilities::Rectangle r2) = 0;
    };
}
