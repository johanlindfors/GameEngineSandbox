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
#include "utilities/AndroidWrapper.hpp"
#include <game-activity/native_app_glue/android_native_app_glue.h>
#include <android/asset_manager.h>

using namespace std;
using namespace Engine;
using namespace Engine;

#define BUFSIZE 1024

namespace Engine {
	class ShaderLoaderImpl 
	{
	public:
		ShaderLoaderImpl() { }

		string loadShader(const string& fileName)
		{
			std::string shader;
			char buf[BUFSIZE];
			auto androidWrapper = IOCContainer::instance().resolve<AndroidWrapper>();
			auto instance = androidWrapper->GetInstance();
			auto assetManager = instance->activity->assetManager;

			auto pAsset = AAssetManager_open(
					assetManager,
					std::string("shaders/" + fileName).c_str(),
					AASSET_MODE_BUFFER);
            auto length = AAsset_getLength(pAsset);
            buf[AAsset_read(pAsset, buf, length)] = 0;
			AAsset_close(pAsset);

			shader = buf;
			return shader;
		}
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
