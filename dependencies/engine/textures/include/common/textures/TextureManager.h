#pragma once
#include <future>
#include <map>

#include "Texture2D.h"
#include "ITextureManager.h"

namespace Engine {
	struct Texture2D;
	class TextureLoader;

	class TextureManager : public ITextureManager {
	public:
		TextureManager();
		~TextureManager();

		// Engine::ITextureManager
		void LoadTextures(std::vector<std::wstring> fileNames) override;
		Texture2D GetTexture(std::wstring fileName) const override;
		bool IsLoaded() const override { return mInitialized; }

	private:
		static Engine::Texture2D CreateEmptyTexture();

		bool mInitialized;
		std::map<std::wstring, Texture2D> mTextures;
		std::unique_ptr<Engine::TextureLoader> mTextureLoader;
	};
}
