#pragma once
#include "Sprite.h"

namespace Engine {
	class ISpriteRenderer {
	public:
		virtual void UpdateWindowSize(GLsizei width, GLsizei height) = 0;
		virtual void Clear() = 0;
		virtual void DrawSprite(Sprite& texture) = 0;
	};
}
