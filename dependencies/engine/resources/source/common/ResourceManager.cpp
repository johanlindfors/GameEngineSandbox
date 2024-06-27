#include "resources/ResourceManager.hpp"
#include "resources/TextureLoader.hpp"
#include "resources/ShaderLoader.hpp"
#include "resources/ObjModelLoader.hpp"
#include "resources/SoundLoader.hpp"
#include "resources/Model.hpp"
#include "resources/Shader.hpp"
#include "resources/Sound.hpp"
#include <memory>
#include "utilities/GLHelper.hpp"
#include "utilities/ALHelper.hpp"
#include "utilities/Logger.hpp"
#include "filesystem/File.hpp"

using namespace std;
using namespace Engine;

ResourceManager::ResourceManager()
	: mInitialized(false)
	, mTextureLoader(make_unique<TextureLoader>())
	, mShaderLoader(make_unique<ShaderLoader>())
	, mModelLoader(make_unique<ObjModelLoader>())
	, mSoundLoader(make_unique<SoundLoader>()) {}

ResourceManager::~ResourceManager()
{
	debuglog << "[ResourceManager::~ResourceManager]" << endl;
	for (const auto &texture : mTextures)
	{
		GlDeleteTextures(1, &texture.second.textureIndex);
	}
	mTextureLoader.reset();
	mShaderLoader.reset();
	mModelLoader.reset();
	for (const auto &sound : mSounds) {
		AlDeleteSources(1, &sound.second.Source);
		AlDeleteBuffers(1, &sound.second.Buffer);
	}
	mSoundLoader.reset();
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
	debuglog << "[ResourceManager::loadTextures]" << endl;
	if (!mInitialized) {
		const auto emptyTexture = createEmptyTexture();
		mTextures[emptyTexture.name] = emptyTexture;
	}
	
	for (auto const& filename : fileNames)
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
		debuglog << "[ResourceManager::loadShader] Loading shader" << endl;
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

void ResourceManager::loadSounds(vector<string> fileNames) {
	for (auto const& filename : fileNames) {
		if (mSounds.find(filename) == mSounds.end())
		{
			debuglog << "[ResourceManager::loadSound] Loading sound '" << filename << "'" << endl;
			const auto sound = mSoundLoader->loadSound(filename);
			mSounds[filename] = sound;
		}
	}
}

Engine::Sound ResourceManager::getSound(const std::string &name) const {
	return mSounds.at(name);
};
