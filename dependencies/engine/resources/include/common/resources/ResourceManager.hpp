#pragma once
#include <future>
#include <map>
#include <vector>
#include <memory>
#include "utilities/MathHelper.hpp"
#include "resources/Model.hpp"
#include "resources/ObjModelLoader.hpp"

namespace Engine
{
	class TextureLoader;
	class ShaderLoader;
	class SoundLoader;
	class MaterialLoader;
	struct Texture2D;
	struct Sound;
	class Shader;
	struct Material;

	class ResourceManager : public IResourceManager
	{
	public:
		ResourceManager();
		~ResourceManager();

		// Engine::IResourceManager
		virtual void loadTextures(std::vector<std::string> fileNames) override;
		virtual Engine::Texture2D getTexture(std::string fileName) const override;
		virtual bool isLoaded() const override { return mInitialized; }

		virtual void loadShader(const std::string &name, const std::string &vsFileName, const std::string &fsFileName) override;
		virtual std::shared_ptr<Engine::Shader> getShader(const std::string &name) const override;

		virtual void loadModel(const std::string &fileName) override;
		virtual std::shared_ptr<Engine::ModelBase> getModel(const std::string &name) const override;

		template <typename T>
        void load(const std::string &fileName){
			auto model = mModelLoader->loadModel<T>(fileName);
			mModels[fileName] = model;
		}

		template <typename T>
        std::shared_ptr<T> get(const std::string &name) const {
            if constexpr (std::is_same<T, Model<Utilities::VertexPositionTexture>>())
            {
                return std::reinterpret_pointer_cast<T>(mModels.at(name));
            }
            return nullptr;
        }

		virtual void loadSounds(std::vector<std::string> fileNames) override;
		virtual Engine::Sound getSound(const std::string &name) const override;

		virtual void loadMaterial(const std::string &fileName) override;
		virtual Engine::Material getMaterial(const std::string &name) const override;

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
