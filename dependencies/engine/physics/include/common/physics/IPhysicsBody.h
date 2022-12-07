#pragma once
#include "utilities/MathHelper.h"

namespace Engine 
{
	class IPhysicsBody
	{
		public: 
			IPhysicsBody(Utilities::Point<float> position) 
				: IsAlive(true)
				, AllowGravity(true)
				, Position(Utilities::Point<float>(position.X, position.Y))
				, Velocity(Utilities::Vector2(0.0f,0.0f))
			{}

			virtual ~IPhysicsBody() = default;

			bool IsAlive;
			bool AllowGravity;
			Utilities::Point<float> Position;
			Utilities::Vector2 Velocity;
	};
}
