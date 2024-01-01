#pragma once
#include "IObjectCollider.hpp"

namespace Engine
{
    class ObjectCollider : public Engine::IObjectCollider
    {
    public:
        bool intersects(Engine::Circle circle, Engine::Rectangle<float> rectangle);
        bool intersects(Engine::Rectangle<float> r1, Engine::Rectangle<float> r2);
    };
}
