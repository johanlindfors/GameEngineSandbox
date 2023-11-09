#pragma once
#include "utilities/MathHelper.hpp"

namespace Engine
{
	struct IPhysicsBody
	{
		IPhysicsBody(Utilities::Point<float> p)
			: isAlive(true), allowGravity(true), position(p), velocity(Utilities::Vector2{0.0f, 0.0f})
		{
		}

		virtual ~IPhysicsBody() = default;

		bool isAlive;
		bool allowGravity;
		Utilities::Point<float> position;
		Utilities::Vector2 velocity;
	};
}
