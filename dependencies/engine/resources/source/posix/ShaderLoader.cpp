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
		{
			mFileSystem = IOCContainer::Instance().Resolve<IFileSystem>();
		}	

		string LoadShader(const string& fileName)
		{
			const auto file = mFileSystem->LoadFile(std::string("shaders/" + fileName), false);
			std::string shader;
			if(file && file->IsOpen()){
				auto fileHandle = file->Get();
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

string ShaderLoader::LoadShader(const string& fileName)
{		
	return mImpl->LoadShader(fileName);
}
