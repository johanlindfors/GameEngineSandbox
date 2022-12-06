#pragma once
#include "textures/Texture2D.h"
#include "utilities/MathHelper.h"

namespace Engine {
	struct Sprite {
		Sprite() 
			: Texture({})
			, Position({ 0, 0 })
			, Velocity({ 0.0f, 0.0f })
			, Width(0)
			, Height(0)
			, Rotation(0.0f)
			, Offset(0)
		{}
		~Sprite() = default;
		
		Texture2D Texture;
		Utilities::Point Position;
		Utilities::Vector2 Velocity;
		int Width;
		int Height;
		float Rotation;
		int Offset;
	};
}
