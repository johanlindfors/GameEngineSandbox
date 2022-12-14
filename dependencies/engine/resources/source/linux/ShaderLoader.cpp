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
	class ShaderLoaderImpl {
	private:
		static string LoadShaderAsString(const string& fileName) {
			return "";
		}

	public:
		ShaderLoaderImpl()
		{
			mFileSystem = IOCContainer::Instance().Resolve<IFileSystem>();
		}	

		string LoadShader(const string& fileName)
		{
			// const auto file = mFileSystem->LoadFile(std::wstring(L"shaders/" + fileName));
			// if(file){
			
			// }
			return string();
		}
	private:
		std::shared_ptr<IFileSystem> mFileSystem;
	};
}

ShaderLoader::ShaderLoader()
	: mImpl(std::make_unique<ShaderLoaderImpl>())
{

}

ShaderLoader::~ShaderLoader()
{
	mImpl.reset(nullptr);
}

string ShaderLoader::LoadShader(const string& fileName)
{		
	return mImpl->LoadShader(fileName);
}
