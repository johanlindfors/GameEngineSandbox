#pragma once
#include "utilities/MathHelper.h"

namespace Engine 
{
    class ICollidable
    {
        public:
            ICollidable(Utilities::Point<float> position)
                : isCollidable(false)
                , AABB(Utilities::Rectangle(
                    position.X,
                    position.Y,
                    0,
                    0))
            { }

   			virtual ~ICollidable() = default;

            bool isCollidable;
            Utilities::Rectangle AABB;
    };
}