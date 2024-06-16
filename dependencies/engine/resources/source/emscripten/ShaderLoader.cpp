#include "resources/ShaderLoader.hpp"
#include "filesystem/FileSystem.hpp"
#include "utilities/IOC.hpp"
#include "utilities/Logger.hpp"
#include "filesystem/File.hpp"
#include "resources/Shader.hpp"
#include <emscripten.h>

using namespace std;
using namespace Engine;
using namespace Utilities;

namespace Engine
{
	class ShaderLoaderImpl
	{
	public:
		ShaderLoaderImpl()
			: mFileSystem(IOCContainer::resolve_type<IFileSystem>()) {}

		string loadShader(const string &fileName)
		{
			const auto file = mFileSystem->loadFile(string("shaders/" + fileName), false);
			debuglog << "[ShaderLoaderImpl::LoadShader] Loading shader" << endl;
			string shader;
			if (file && file->isOpen())
			{
				shader = file->readAllText();
			}
			return shader;
		}

	private:
		shared_ptr<IFileSystem> mFileSystem;
	};
}

ShaderLoader::ShaderLoader()
	: mImpl(std::make_unique<ShaderLoaderImpl>()) {

	EM_ASM(
    	FS.mkdir('/shaders');
    	FS.mount(MEMFS, {}, '/shaders');
    );
	}

ShaderLoader::~ShaderLoader()
{
	mImpl.reset(nullptr);
}

string ShaderLoader::loadShader(const string &fileName)
{
	return mImpl->loadShader(fileName);
}
