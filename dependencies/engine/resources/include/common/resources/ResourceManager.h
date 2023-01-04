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
		void loadTextures(std::vector<std::string> fileNames) override;
		Texture2D getTexture(std::string fileName) const override;
		bool isLoaded() const override { return mInitialized; }

		void loadShader(const std::string& name, const std::string& vsFileName, const std::string& fsFileName) override;
		std::shared_ptr<Shader> getShader(const std::string& name) const override;

	private:
		static Engine::Texture2D createEmptyTexture();

		bool mInitialized;
		std::map<std::string, Texture2D> mTextures;
		std::map<std::string, std::shared_ptr<Shader> > mShaders;
		std::unique_ptr<Engine::TextureLoader> mTextureLoader;
		std::unique_ptr<Engine::ShaderLoader> mShaderLoader;
	};
}
