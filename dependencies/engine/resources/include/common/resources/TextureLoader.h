#pragma once
#include <memory>

#define EMPTY_TEXTURE_NAME "empty"

namespace Engine {
	class TextureLoaderImpl;
	struct Texture2D;

	class TextureLoader {
	public:
		TextureLoader();
		~TextureLoader();

		void loadTexture(Engine::Texture2D& texture);

	private:
		std::unique_ptr<TextureLoaderImpl> mImpl;
	};
}
