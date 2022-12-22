#pragma once
#include <future>
#include <map>
#include "IResourceManager.h"

namespace Engine {
	struct Texture2D;
	class Shader;
	class TextureLoader;
	class ShaderLoader;

	class ResourceManager : public IResourceManager {
	public:
		ResourceManager();
		~ResourceManager();

		// Engine::IResourceManager
		void LoadTextures(std::vector<std::string> fileNames) override;
		Texture2D GetTexture(std::string fileName) const override;
		bool IsLoaded() const override { return mInitialized; }

		void LoadShaders(const std::string& vsFileName, const std::string& fsFileName);
		Shader GetShader(const std::string& name);

	private:
		static Engine::Texture2D CreateEmptyTexture();

		bool mInitialized;
		std::map<std::string, Texture2D> mTextures;
		std::map<std::string, Shader> mShaders;
		std::unique_ptr<Engine::TextureLoader> mTextureLoader;
		// std::unique_ptr<Engine::ShaderLoader> mShaderLoader;
	};
}
