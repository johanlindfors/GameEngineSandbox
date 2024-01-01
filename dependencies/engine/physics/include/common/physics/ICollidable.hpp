#pragma once
#include "utilities/MathHelper.hpp"

namespace Engine
{
    class ICollidable
    {
    public:
        ICollidable(Engine::Point<float> position)
            : isCollidable(false), AABB(Engine::Rectangle<float>(
                                       position.x,
                                       position.y,
                                       0.0f,
                                       0.0f))
        {
        }

        virtual ~ICollidable() = default;

        bool isCollidable;
        Engine::Rectangle<float> AABB;
    };
}