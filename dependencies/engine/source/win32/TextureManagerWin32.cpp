#include "textures/TextureManager.h"
#include "GLHelper.h"

using namespace std;
#define EMPTY_TEXTURE_NAME L"empty"

class TextureManagerImpl {
public:
	void LoadTexture(Texture2D& texture)
	{
		texture.Name = L"";
	}

	Texture2D CreateEmptyTexture() {
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
};

TextureManager::TextureManager()
	: mInitialized(false)
	, mImpl(new TextureManagerImpl())
{

}

TextureManager::~TextureManager()
{
	delete(mImpl);
}

void TextureManager::LoadTextures(vector<wstring> filenames) {
	if (!mInitialized) {
		auto emptyTexture = mImpl->CreateEmptyTexture();
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
		mImpl->LoadTexture(texture.second);
	}
	mInitialized = true;
}

Texture2D TextureManager::GetTexture(wstring filename) const {
	if (mTextures.count(filename) == 1) {
		auto texture = mTextures.at(filename);
		if (texture.Name == filename) {
			return texture;
		}
	}
	return mTextures.at(EMPTY_TEXTURE_NAME);
}