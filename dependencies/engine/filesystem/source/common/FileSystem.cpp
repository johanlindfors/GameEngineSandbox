#include "filesystem/FileSystem.hpp"
#include "filesystem/File.hpp"
#include "utilities/Config.hpp"
#include "utilities/IOC.hpp"

#ifdef UWP
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.ApplicationModel.h>
using namespace winrt;
using namespace Windows::Storage;
using namespace Windows::ApplicationModel;
#elif WIN32
#include <Windows.h>
#include <vector>
#include <filesystem>
namespace fs = std::filesystem;
#elif defined(PLATFORM_POSIX)
#include <filesystem>
namespace fs = std::filesystem;
#endif

using namespace std;
using namespace Engine;

string FileSystem::getAssetsDirectory()
{
	string path;
	auto config = Utilities::IOCContainer::instance().resolve<Utilities::Config>();
#ifdef UWP
	const auto folder = Package::Current().InstalledLocation();
	const auto folderPath = folder.Path();
	path = std::string(folderPath + L"\\assets\\");    
#elif WIN32
	const unsigned int bufferSize = 512;
	vector<char> buffer(bufferSize + 1);
	::GetModuleFileName(nullptr, &buffer[0], bufferSize);
	const string s = &buffer[0];
	const fs::path p(s);
	const auto executableDirectory = p.parent_path();
	const auto folderPath = executableDirectory.generic_string();
	path =  std::string(folderPath + "/assets/");
#elif defined(PLATFORM_POSIX)
	std::string current_working_dir(fs::current_path().generic_string());
	path = string(current_working_dir + "/games/" + config->executable + "/assets/");
#else
	static_assert("Invalid platform configured");
#endif
	printf("=== %s\n", path.c_str());
    return path;
}

std::shared_ptr<File> FileSystem::loadFile(std::string filename, bool writeable)
{
	const auto directory = getAssetsDirectory();
	auto file = std::make_shared<File>();
	file->open(directory + filename, writeable);
	return file;
}