#pragma once

namespace Utilities
{
    struct Circle;
    struct Rectangle;

    class IObjectCollider {
    public:
        virtual bool intersects(Utilities::Circle circle, Utilities::Rectangle rectangle) = 0;
        virtual bool intersects(Utilities::Rectangle r1, Utilities::Rectangle r2) = 0;
    };
}
