#pragma once
#include <future>
#include <map>
#include <vector>
#include <memory>

namespace Engine
{
	class TextureLoader;
	class ShaderLoader;
	class ObjModelLoader;
	class SoundLoader;
	class MaterialLoader;
	class Sound;

	class ResourceManager 
	{
	public:
		ResourceManager();
		~ResourceManager();

		// Engine::IResourceManager
		void loadTextures(std::vector<std::string> fileNames);
		Engine::Texture2D getTexture(std::string fileName) const;
		bool isLoaded() const { return mInitialized; }

		void loadShader(const std::string &name, const std::string &vsFileName, const std::string &fsFileName);
		std::shared_ptr<Engine::Shader> getShader(const std::string &name) const;

		template <class T>
        void load(const std::string &fileName);
		template <class T>
        std::shared_ptr<T> get(const std::string &name) const;

		void loadSounds(std::vector<std::string> fileNames);
		Engine::Sound getSound(const std::string &name) const;

		void loadMaterial(const std::string &fileName);
		Engine::Material getMaterial(const std::string &name) const;

	private:
		static Engine::Texture2D createEmptyTexture();

		bool mInitialized;
		std::map<std::string, Texture2D> mTextures;
		std::map<std::string, Sound> mSounds;
		std::map<std::string, std::shared_ptr<Shader>> mShaders;
		std::map<std::string, std::shared_ptr<ModelBase>> mModels;
		std::map<std::string, Material> mMaterials;
		std::unique_ptr<Engine::TextureLoader> mTextureLoader;
		std::unique_ptr<Engine::ShaderLoader> mShaderLoader;
		std::unique_ptr<Engine::ObjModelLoader> mModelLoader;
		std::unique_ptr<Engine::SoundLoader> mSoundLoader;
		std::unique_ptr<Engine::MaterialLoader> mMaterialLoader;
	};
}
