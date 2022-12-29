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
		virtual void Initialize() = 0;
		virtual void UpdateWindowSize(int width, int height) = 0;
		virtual void Clear() = 0;

		virtual void DrawSprite(std::shared_ptr<Sprite> sprite) = 0;
		virtual void DrawSprite(std::shared_ptr<Sprite> sprite, Utilities::Point<float> position) = 0;
	};
}
