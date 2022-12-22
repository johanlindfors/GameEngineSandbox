#pragma once
#include <vector>
#include <string>
#include "Texture2D.h"

namespace Engine {
	class IResourceManager 
	{
	public:
		virtual ~IResourceManager() = default;
		virtual void LoadTextures(std::vector<std::string> fileNames) = 0;
		virtual Texture2D GetTexture(std::string fileName) const = 0;
		virtual bool IsLoaded() const = 0;
	};
}
