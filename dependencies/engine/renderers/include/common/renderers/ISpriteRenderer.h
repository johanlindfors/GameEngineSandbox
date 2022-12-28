#pragma once
#include <memory>
#include "glwrapper.h"
#include "utilities/MathHelper.h"

namespace Engine {
	struct Sprite;

	class ISpriteRenderer {
	public:
		virtual ~ISpriteRenderer() = default;
		virtual void Initialize() = 0;
		virtual void UpdateWindowSize(GLsizei width, GLsizei height) = 0;
		virtual void Clear() = 0;
		virtual void DrawSprite(std::shared_ptr<Sprite> sprite) = 0;
		virtual void DrawSprite(std::shared_ptr<Sprite> sprite, Utilities::Point<float> position) = 0;
	};
}
