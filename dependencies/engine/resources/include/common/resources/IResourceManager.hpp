#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Texture2D.hpp"

namespace Engine {
	class Shader;
	class Model;

	class IResourceManager
	{
	public:
		virtual void loadTextures(std::vector<std::string> fileNames) = 0;
		virtual Texture2D getTexture(std::string fileName) const = 0;
		virtual void loadShader(const std::string& name, const std::string& vsFilename, const std::string& fsFilename) = 0;
		virtual std::shared_ptr<Shader> getShader(const std::string& name) const = 0;
		virtual bool isLoaded() const = 0;

		virtual void loadModel(const std::string& fileName) = 0;
		virtual std::shared_ptr<Engine::Model> getModel(const std::string& name) const = 0;

	};
}
