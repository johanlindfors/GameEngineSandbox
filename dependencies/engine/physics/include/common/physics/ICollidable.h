#pragma once
#include "MathHelper.h"

namespace Engine 
{
    class ICollidable
    {
        public:
            ICollidable(Utilities::Vector2 position)
                : IsCollidable(false)
                , AABB(Utilities::Rectangle(
                    position.m[0],
                    position.m[1],
                    0,
                    0))
            { }

   			virtual ~ICollidable() = default;


            bool IsCollidable;
            //Action<ICollidable> OnCollideWith { get; set; }
            Utilities::Rectangle AABB;
    };
}