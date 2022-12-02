#pragma once
#include "MathHelper.h"

namespace Engine 
{
	class IPhysicsBody
	{
		public: 
			IPhysicsBody(Utilities::Vector2 position) 
				: IsAlive(true)
				, X(position.m[0])
				, Y(position.m[1])
				, Velocity(Utilities::Vector2(0.0f,0.0f))
				, AllowGravity(true)
			{}

			virtual ~IPhysicsBody() = default;

			bool IsAlive;
			float X;
			float Y;
			Utilities::Vector2 Velocity;
			bool AllowGravity;
	};
}
