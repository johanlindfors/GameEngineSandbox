#pragma once
#include <future>
#include <map>
#include "IResourceManager.hpp"

namespace Engine
{
	struct Texture2D;
	class Shader;
	class Model;
	class TextureLoader;
	class ShaderLoader;
	class ModelLoader;
	class SoundLoader;

	class ResourceManager : public IResourceManager
	{
	public:
		ResourceManager();
		~ResourceManager();

		// Engine::IResourceManager
		void loadTextures(std::vector<std::string> fileNames) override;
		Engine::Texture2D getTexture(std::string fileName) const override;
		bool isLoaded() const override { return mInitialized; }

		void loadShader(const std::string &name, const std::string &vsFileName, const std::string &fsFileName) override;
		std::shared_ptr<Engine::Shader> getShader(const std::string &name) const override;

		void loadModel(const std::string &fileName) override;
		std::shared_ptr<Engine::Model> getModel(const std::string &name) const override;

		void loadSounds(std::vector<std::string> fileNames) override;
		Engine::Sound getSound(const std::string &name) const override;

	private:
		static Engine::Texture2D createEmptyTexture();

		bool mInitialized;
		std::map<std::string, Texture2D> mTextures;
		std::map<std::string, Sound> mSounds;
		std::map<std::string, std::shared_ptr<Shader>> mShaders;
		std::map<std::string, std::shared_ptr<Model>> mModels;
		std::unique_ptr<Engine::TextureLoader> mTextureLoader;
		std::unique_ptr<Engine::ShaderLoader> mShaderLoader;
		std::unique_ptr<Engine::ModelLoader> mModelLoader;
		std::unique_ptr<Engine::SoundLoader> mSoundLoader;
	};
}
