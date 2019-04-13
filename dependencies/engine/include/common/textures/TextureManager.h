#pragma once
#include <future>
#include <map>

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Windows.Graphics.Imaging.h>
#include <winrt/Windows.UI.Core.h>
#include "Texture2D.h"

class TextureManagerImpl;

class TextureManager {
public:
	TextureManager()
		: mIsLoaded(false)
    { }

	void LoadTextures(std::vector<std::wstring> filename);
	Texture2D GetTexture(std::wstring filename);
	bool IsLoaded() { return mIsLoaded; }

private:
	GLuint GenerateTexture();
	std::future<void> LoadTextureAsync(Texture2D& texture);
	void SetTexturePixels(GLuint textureId, GLsizei width, GLsizei height, GLubyte* pixels);

	bool mIsLoaded;
    std::map<std::wstring, Texture2D> mTextures;

    TextureManagerImpl* mImpl;
};
