#pragma once

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
		TextureLoaderImpl* mImpl;
	};
}
