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

Texture2D ResourceManager::CreateEmptyTexture() {
	Texture2D texture;
	texture.TextureIndex = GenerateTexture();
	texture.Width = 1;
	texture.Height = 1;
	texture.Name = EMPTY_TEXTURE_NAME;

	const auto pixels = new GLubyte[4]{ 255, 0, 255 , 255 };
	SetTexturePixels(texture.TextureIndex, texture.Width, texture.Height, true, pixels);
	delete[] pixels;

	return texture;
}

void ResourceManager::LoadTextures(vector<string> fileNames)
{
	printf("[ResourceManager::LoadTextures]\n");
	if (!mInitialized) {
		const auto emptyTexture = CreateEmptyTexture();
		mTextures[emptyTexture.Name] = emptyTexture;
	}

	for (auto const& filename : fileNames)
	{
		Texture2D texture;
		texture.Name = filename;
		texture.TextureIndex = GenerateTexture();
		mTextures[filename] = texture;
	}

	for (auto& texture : mTextures)
	{
		if (!texture.second.IsLoaded) {
			mTextureLoader->LoadTexture(texture.second);
			texture.second.IsLoaded = true;
		}
	}

	mInitialized = true;
}

Texture2D ResourceManager::GetTexture(string fileName) const
{
	if (mTextures.count(fileName) == 1) {
		auto texture = mTextures.at(fileName);
		if (texture.Name == fileName) {
			return texture;
		}
	}
	return mTextures.at(EMPTY_TEXTURE_NAME);
}

void ResourceManager::LoadShader(const string& name, const string& vsFileName, const string& fsFileName)
{
	const auto vs = mShaderLoader->LoadShader(vsFileName);
	const auto fs = mShaderLoader->LoadShader(fsFileName);
	auto shader = make_shared<Shader>();
	shader->CreateShader(name, vs, fs);
	mShaders[name] = shader;
}

shared_ptr<Shader> ResourceManager::GetShader(const string& name) const
{
	return mShaders.at(name);
}