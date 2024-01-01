#pragma once
#include "utilities/MathHelper.hpp"

namespace Engine
{
	struct IPhysicsBody
	{
		IPhysicsBody(Engine::Point<float> p)
			: isAlive(true), allowGravity(true), position(p), velocity(Engine::Vector2{0.0f, 0.0f})
		{
		}

		virtual ~IPhysicsBody() = default;

		bool isAlive;
		bool allowGravity;
		Engine::Point<float> position;
		Engine::Vector2 velocity;
	};
}
