#pragma once
#include <vector>
#include <string>
#include "Texture2D.h"

namespace Engine {
	class ITextureManager 
	{
	public:
		virtual void LoadTextures(std::vector<std::wstring> filename) = 0;
		virtual Texture2D GetTexture(std::wstring filename) const = 0;
		virtual bool IsLoaded() const = 0;
	};
}
