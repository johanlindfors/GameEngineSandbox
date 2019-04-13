#pragma once
#include <future>
#include <map>

#include "Texture2D.h"
#include "ITextureManager.h"

class TextureManagerImpl;

class TextureManager : public ITextureManager {
public:
	TextureManager();
	~TextureManager();

	void LoadTextures(std::vector<std::wstring> filenames);
	Texture2D GetTexture(std::wstring filename) const;
	bool IsLoaded() const { return mInitialized; }

private:
	bool mInitialized;
    std::map<std::wstring, Texture2D> mTextures;
    TextureManagerImpl* mImpl;
};
