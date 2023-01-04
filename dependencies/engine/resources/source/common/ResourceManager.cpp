#include "resources/ResourceManager.h"
#include "resources/TextureLoader.h"
#include "resources/ShaderLoader.h"
#include "resources/Shader.h"
#include <memory>
#include "utilities/GLHelper.h"
#include "File.h"

using namespace std;
using namespace Engine;

ResourceManager::ResourceManager()
	: mInitialized(false)
	, mTextureLoader(make_unique<TextureLoader>())
	, mShaderLoader(make_unique<ShaderLoader>()) { }

ResourceManager::~ResourceManager()
{
	mTextureLoader.reset();
	mShaderLoader.reset();
}

Texture2D ResourceManager::createEmptyTexture() {
	Texture2D texture;
	texture.textureIndex = generateTexture();
	texture.width = 1;
	texture.height = 1;
	texture.name = EMPTY_TEXTURE_NAME;

	const auto pixels = new GLubyte[4]{ 255, 0, 255 , 255 };
	setTexturePixels(texture.textureIndex, texture.width, texture.height, true, pixels);
	delete[] pixels;

	return texture;
}

void ResourceManager::loadTextures(vector<string> fileNames)
{
	printf("[ResourceManager::loadTextures]\n");
	if (!mInitialized) {
		const auto emptyTexture = createEmptyTexture();
		mTextures[emptyTexture.name] = emptyTexture;
	}

	for (auto const& filename : fileNames)
	{
		Texture2D texture;
		texture.name = filename;
		texture.textureIndex = generateTexture();
		mTextures[filename] = texture;
	}

	for (auto& texture : mTextures)
	{
		if (!texture.second.isLoaded) {
			mTextureLoader->loadTexture(texture.second);
			texture.second.isLoaded = true;
		}
	}

	mInitialized = true;
}

Texture2D ResourceManager::getTexture(string fileName) const
{
	if (mTextures.count(fileName) == 1) {
		auto texture = mTextures.at(fileName);
		if (texture.name == fileName) {
			return texture;
		}
	}
	return mTextures.at(EMPTY_TEXTURE_NAME);
}

void ResourceManager::loadShader(const string& name, const string& vsFileName, const string& fsFileName)
{
    printf("[ResourceManager::loadShader] Loading shader\n");
	const auto vs = mShaderLoader->loadShader(vsFileName);
	const auto fs = mShaderLoader->loadShader(fsFileName);
	auto shader = make_shared<Shader>();
	shader->createShader(name, vs, fs);
	mShaders[name] = shader;
}

shared_ptr<Shader> ResourceManager::getShader(const string& name) const
{
	return mShaders.at(name);
}