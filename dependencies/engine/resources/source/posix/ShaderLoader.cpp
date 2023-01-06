#include "resources/ShaderLoader.h"
#include "filesystem/FileSystem.h"
#include "utilities/GLHelper.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include "utilities/IOC.hpp"
#include "File.h"
#include "resources/Shader.h"

using namespace std;
using namespace Engine;
using Utilities::IOCContainer;

namespace Engine {
	class ShaderLoaderImpl 
	{
	public:
		ShaderLoaderImpl()
			: mFileSystem(IOCContainer::instance().resolve<IFileSystem>()) { }	

		string loadShader(const string& fileName)
		{
			const auto file = mFileSystem->loadFile(std::string("shaders/" + fileName), false);
		    printf("[ShaderLoaderImpl::LoadShader] Loading shader\n");
			std::string shader;
			if(file && file->isOpen()){
				auto fileHandle = file->get();
				char buffer[100];
				while(!feof(fileHandle)) {
					if(fgets(buffer, 100, fileHandle) != NULL)
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
	: mImpl(std::make_unique<ShaderLoaderImpl>()) { }

ShaderLoader::~ShaderLoader()
{
	mImpl.reset(nullptr);
}

string ShaderLoader::loadShader(const string& fileName)
{		
	return mImpl->loadShader(fileName);
}
