#pragma once
#include <memory>
#include "IRenderer.h"
#include "utilities/MathHelper.h"

namespace Engine {
	struct Sprite;

	class ISpriteRenderer : public IRenderer {
	public:
		virtual ~ISpriteRenderer() = default;
		
		// Engine::IRenderer
		virtual void initialize() = 0;
		virtual void updateWindowSize(int width, int height) = 0;
		virtual void clear() = 0;

		virtual void drawSprite(std::shared_ptr<Sprite> sprite) = 0;
		virtual void drawSprite(std::shared_ptr<Sprite> sprite, Utilities::Point<float> position) = 0;
	};
}
