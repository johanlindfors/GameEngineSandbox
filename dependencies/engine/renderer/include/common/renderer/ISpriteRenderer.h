#pragma once
#include <memory>
#include "glwrapper.h"

namespace Utilities
{
	struct Point;
}

namespace Engine {
	struct Sprite;

	class ISpriteRenderer {
	public:
		virtual ~ISpriteRenderer() = default;
		virtual void Initialize() = 0;
		virtual void UpdateWindowSize(GLsizei width, GLsizei height) = 0;
		virtual void Clear() = 0;
		virtual void DrawSprite(std::shared_ptr<Sprite> sprite) = 0;
		virtual void DrawSprite(std::shared_ptr<Sprite> sprite, Utilities::Point position) = 0;
	};
}
