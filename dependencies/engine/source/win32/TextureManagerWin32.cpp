#include "textures/TextureManager.h"

using namespace std;


class TextureManagerImpl {
public:
	void LoadTexture(Texture2D& texture)
	{

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
	return mTextures.at(filename);
}