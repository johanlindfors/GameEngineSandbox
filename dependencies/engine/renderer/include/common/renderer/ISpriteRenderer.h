#pragma once
#include <memory>
#include "glwrapper.h"

namespace Engine {
	struct Sprite;

	class ISpriteRenderer {
	public:
		virtual ~ISpriteRenderer() = default;
		virtual void UpdateWindowSize(GLsizei width, GLsizei height) = 0;
		virtual void Clear() = 0;
		virtual void DrawSprite(std::shared_ptr<Sprite> texture) = 0;
	};
}
