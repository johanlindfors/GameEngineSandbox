#pragma once
#include "utilities/MathHelper.hpp"

namespace Engine
{
    class ICollidable
    {
    public:
        ICollidable(Utilities::Point<float> position)
            : isCollidable(false), AABB(Utilities::Rectangle<float>(
                                       position.x,
                                       position.y,
                                       0.0f,
                                       0.0f))
        {
        }

        virtual ~ICollidable() = default;

        bool isCollidable;
        Utilities::Rectangle<float> AABB;
    };
}