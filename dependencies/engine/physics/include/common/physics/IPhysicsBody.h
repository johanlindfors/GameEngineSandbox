#pragma once
#include "MathHelper.h"

namespace Engine {
	class IPhysicsBody {
		public: 
			IPhysicsBody() 
				: IsAlive(true)
				, X(0)
				, Y(0)
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
