#pragma once
#include "utilities/MathHelper.h"

namespace Engine 
{
	class IPhysicsBody
	{
		public: 
			IPhysicsBody(Utilities::Point position) 
				: IsAlive(true)
				, AllowGravity(true)
				, Position(position)
				, Velocity(Utilities::Vector2(0.0f,0.0f))
			{}

			virtual ~IPhysicsBody() = default;

			bool IsAlive;
			bool AllowGravity;
			Utilities::Point Position;
			Utilities::Vector2 Velocity;
	};
}
