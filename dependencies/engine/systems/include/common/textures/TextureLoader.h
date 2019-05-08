#pragma once
#include <memory>

#define EMPTY_TEXTURE_NAME L"empty"

namespace Engine {
	class TextureLoaderImpl;
	struct Texture2D;

	class TextureLoader {
	public:
		TextureLoader();
		~TextureLoader();

		void LoadTexture(Engine::Texture2D& texture);

	private:
		std::unique_ptr<TextureLoaderImpl> mImpl;
	};
}
