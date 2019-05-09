#include "textures/TextureManager.h"
#include "textures/TextureLoader.h"
#include <memory>
#include <algorithm>
#include "GLHelper.h"
#include "filesystem/FileSystem.h"
#include "File.h"

using namespace std;
using namespace Engine;

TextureManager::TextureManager()
	: mInitialized(false)
	, mTextureLoader(make_unique<TextureLoader>())
{

}

TextureManager::~TextureManager()
{
	mTextureLoader.reset();
}

Texture2D TextureManager::CreateEmptyTexture() {
	Texture2D texture;
	texture.TextureIndex = GenerateTexture();
	texture.Width = 1;
	texture.Height = 1;
	texture.Name = EMPTY_TEXTURE_NAME;

	auto pixels = new GLubyte[4]{ 255, 0, 255 , 255 };
	SetTexturePixels(texture.TextureIndex, texture.Width, texture.Height, pixels);
	delete[] pixels;

	return texture;
}

void TextureManager::LoadTextures(vector<wstring> filenames)
{
	if (!mInitialized) {
		auto emptyTexture = CreateEmptyTexture();
		mTextures[emptyTexture.Name] = emptyTexture;
	}

	for (auto const& filename : filenames)
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

Texture2D TextureManager::GetTexture(wstring filename) const
{
	if (mTextures.count(filename) == 1) {
		auto texture = mTextures.at(filename);
		if (texture.Name == filename) {
			return texture;
		}
	}
	return mTextures.at(EMPTY_TEXTURE_NAME);
}