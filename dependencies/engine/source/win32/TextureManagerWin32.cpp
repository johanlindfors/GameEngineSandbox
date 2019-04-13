#include "textures/TextureManager.h"

using namespace std;

class TextureManagerImpl {

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

void TextureManager::LoadTextures(vector<wstring> textures) {
    mInitialized = true;
}

Texture2D TextureManager::GetTexture(wstring filename) const {
    return Texture2D();
}