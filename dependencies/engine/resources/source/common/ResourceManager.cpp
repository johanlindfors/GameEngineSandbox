#include "resources/ResourceManager.hpp"
#include "resources/TextureLoader.hpp"
#include "resources/ShaderLoader.hpp"
#include "resources/ModelLoader.hpp"
#include "resources/Model.hpp"
#include "resources/Shader.hpp"
#include <memory>
#include "utilities/GLHelper.hpp"
#include "filesystem/File.hpp"

using namespace std;
using namespace Engine;

ResourceManager::ResourceManager()
	: mInitialized(false), mTextureLoader(make_unique<TextureLoader>()), mShaderLoader(make_unique<ShaderLoader>()), mModelLoader(make_unique<ModelLoader>()) {}

ResourceManager::~ResourceManager()
{
	mTextureLoader.reset();
	mShaderLoader.reset();
	mModelLoader.reset();
}

Texture2D ResourceManager::createEmptyTexture()
{
	Texture2D texture;
	texture.textureIndex = generateTexture();
	texture.width = 1;
	texture.height = 1;
	texture.name = EMPTY_TEXTURE_NAME;

	const auto pixels = new GLubyte[4]{255, 0, 255, 255};
	setTexturePixels(texture.textureIndex, texture.width, texture.height, true, pixels);
	delete[] pixels;

	return texture;
}

void ResourceManager::loadTextures(vector<string> fileNames)
{
	printf("[ResourceManager::loadTextures]\n");
	if (!mInitialized)
	{
		const auto emptyTexture = createEmptyTexture();
		mTextures[emptyTexture.name] = emptyTexture;
	}

	for (auto const &filename : fileNames)
	{
		if (mTextures.find(filename) == mTextures.end())
		{
			Texture2D texture;
			texture.name = filename;
			texture.textureIndex = generateTexture();
			mTextures[filename] = texture;
		}
	}

	for (auto &texture : mTextures)
	{
		if (!texture.second.isLoaded)
		{
			mTextureLoader->loadTexture(texture.second);
			texture.second.isLoaded = true;
		}
	}

	mInitialized = true;
}

Texture2D ResourceManager::getTexture(string fileName) const
{
	if (mTextures.count(fileName) == 1)
	{
		auto texture = mTextures.at(fileName);
		if (texture.name == fileName)
		{
			return texture;
		}
	}
	return mTextures.at(EMPTY_TEXTURE_NAME);
}

void ResourceManager::loadShader(const string &name, const string &vsFileName, const string &fsFileName)
{
	if (mShaders.find(name) == mShaders.end())
	{
		printf("[ResourceManager::loadShader] Loading shader\n");
		const auto vs = mShaderLoader->loadShader(vsFileName);
		const auto fs = mShaderLoader->loadShader(fsFileName);

		auto shader = make_shared<Shader>();
		shader->createShader(name, vs, fs);
		mShaders[name] = shader;
	}
}

shared_ptr<Shader> ResourceManager::getShader(const string &name) const
{
	return mShaders.at(name);
}

void ResourceManager::loadModel(const string &fileName)
{
	if (mModels.find(fileName) == mModels.end())
	{

		const auto model = mModelLoader->loadModel(fileName);
		mModels[fileName] = model;
	}
}

shared_ptr<Model> ResourceManager::getModel(const string &name) const
{
	return mModels.at(name);
}
