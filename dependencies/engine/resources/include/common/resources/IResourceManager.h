#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Texture2D.h"

namespace Engine {
	class Shader;

	class IResourceManager
	{
	public:
		virtual void LoadTextures(std::vector<std::string> fileNames) = 0;
		virtual Texture2D GetTexture(std::string fileName) const = 0;
		virtual void LoadShader(const std::string& name, const std::string& vsFilename, const std::string& fsFilename) = 0;
		virtual std::shared_ptr<Shader> GetShader(const std::string& name) const = 0;
		virtual bool IsLoaded() const = 0;
	};
}
