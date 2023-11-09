#include "resources/ShaderLoader.hpp"
#include "filesystem/FileSystem.hpp"
#include "utilities/GLHelper.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include "utilities/IOC.hpp"
#include "filesystem/File.hpp"
#include "resources/Shader.hpp"

using namespace std;
using namespace Engine;
using Utilities::IOCContainer;

namespace Engine
{
	class ShaderLoaderImpl
	{
	public:
		ShaderLoaderImpl()
			: mFileSystem(IOCContainer::instance().resolve<IFileSystem>()) {}

		string loadShader(const string &fileName)
		{
			const auto file = mFileSystem->loadFile(std::string("shaders/" + fileName), false);
			std::string shader;
			if (file && file->isOpen())
			{
				auto fileHandle = file->get();
				char buffer[100];
				while (!feof(fileHandle))
				{
					if (fgets(buffer, 100, fileHandle) != NULL)
						shader += buffer;
				}
			}
			return shader;
		}

	private:
		std::shared_ptr<IFileSystem> mFileSystem;
	};
}

ShaderLoader::ShaderLoader()
	: mImpl(std::make_unique<ShaderLoaderImpl>()) {}

ShaderLoader::~ShaderLoader()
{
	mImpl.reset(nullptr);
}

string ShaderLoader::loadShader(const string &fileName)
{
	return mImpl->loadShader(fileName);
}
