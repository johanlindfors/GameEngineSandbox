#include "filesystem/FileSystem.h"
#include "File.h"

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
#elif __APPLE__
#include <stdio.h>
#include <unistd.h>
#include <filesystem>
namespace fs = std::filesystem;
#elif __linux__
#include <filesystem>
namespace fs = std::filesystem;
#endif

using namespace std;
using namespace Engine;

string FileSystem::getResourcesDirectory()
{
	string path;
#ifdef UWP
	const auto folder = Package::Current().InstalledLocation();
	const auto folderPath = folder.Path();
	path = std::string(folderPath + L"\\resources\\");    
#elif WIN32
	const unsigned int bufferSize = 512;
	vector<char> buffer(bufferSize + 1);
	::GetModuleFileName(nullptr, &buffer[0], bufferSize);
	const string s = &buffer[0];
	const fs::path p(s);
	const auto executableDirectory = p.parent_path();
	const auto folderPath = executableDirectory.generic_string();
	path =  std::string(folderPath + "/resources/");
#elif __APPLE__
	std::string current_working_dir(fs::current_path().generic_string());
	path = string(current_working_dir + "/");
#elif __linux__
	std::string current_working_dir(fs::current_path().generic_string());
	path = string(current_working_dir + "/resources/");
#endif
	//printf("=== %s\n", path.c_str());
    return path;
}

std::shared_ptr<File> FileSystem::loadFile(std::string filename, bool writeable)
{
	const auto directory = getResourcesDirectory();
	auto file = std::make_shared<File>();
	file->open(directory + filename, writeable);
	return file;
}