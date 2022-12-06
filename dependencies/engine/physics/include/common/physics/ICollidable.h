#pragma once
#include "utilities/MathHelper.h"

namespace Engine 
{
    class ICollidable
    {
        public:
            ICollidable(Utilities::Point position)
                : IsCollidable(false)
                , AABB(Utilities::Rectangle(
                    position.X,
                    position.Y,
                    0,
                    0))
            { }

   			virtual ~ICollidable() = default;

            bool IsCollidable;
            Utilities::Rectangle AABB;
    };
}