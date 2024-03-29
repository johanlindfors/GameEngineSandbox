#pragma once
#include <memory>
#include <string>

namespace Engine
{
	class ShaderLoaderImpl;
	class Shader;

	class ShaderLoader
	{
	public:
		ShaderLoader();
		~ShaderLoader();

		std::string loadShader(const std::string &fileName);

	private:
		std::unique_ptr<ShaderLoaderImpl> mImpl;
	};
}
