#pragma once
#include "resources/Texture2D.hpp"
#include "utilities/MathHelper.hpp"
#include <cstdio>

namespace Engine
{
	struct Sprite
	{
		Sprite()
			: texture({}), position({0.0f, 0.0f}), velocity({0.0f, 0.0f}), size({0.0f, 0.0f}), rotation(0.0f), offset({0.0f, 0.0f, 1.0f, 1.0f})
		{
		}
		~Sprite() = default;

		Texture2D texture;
		Engine::Point<float> position;
		Engine::Vector2 velocity;
		Engine::Size<float> size;
		float rotation;
		Engine::Rectangle<float> offset;
	};
}
