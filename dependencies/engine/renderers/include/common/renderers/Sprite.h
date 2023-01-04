#pragma once
#include "resources/Texture2D.h"
#include "utilities/MathHelper.h"

namespace Engine {
	struct Sprite {
		Sprite() 
			: texture({})
			, position({ 0, 0 })
			, velocity({ 0.0f, 0.0f })
			, width(0)
			, height(0)
			, rotation(0.0f)
			, offset(0)
		{}
		~Sprite() = default;
		
		Texture2D texture;
		Utilities::Point<float> position;
		Utilities::Vector2 velocity;
		int width;
		int height;
		float rotation;
		int offset;
	};
}
