#pragma once
#include "utilities/MathHelper.hpp"

namespace Engine
{
    class IObjectCollider
    {
    public:
        virtual bool intersects(Engine::Circle circle, Engine::Rectangle<float> rectangle) = 0;
        virtual bool intersects(Engine::Rectangle<float> r1, Engine::Rectangle<float> r2) = 0;
    };
}
