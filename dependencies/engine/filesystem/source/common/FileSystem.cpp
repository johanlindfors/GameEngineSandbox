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
namespace fs s= std::filesystem;
#elif OSX
#include <stdio.h>
#include <unistd.h>
#elif __linux__
#include <vector>
#include <filesystem>
#include <libgen.h>
#include <stdio.h>
#include <unistd.h>
namespace fs = std::filesystem;
#endif

using namespace std;
using namespace Engine;

wstring FileSystem::GetResourcesDirectory()
{
	std::wstring folderPath;
	wstring path;
#ifdef UWP
	const auto folder = Package::Current().InstalledLocation();
	const auto folderPath = folder.Path();
	path = std::wstring(folderPath + L"\\resources\\");    
#elif WIN32
	const unsigned int bufferSize = 512;
	vector<char> buffer(bufferSize + 1);
	::GetModuleFileName(nullptr, &buffer[0], bufferSize);
	const string s = &buffer[0];
	const fs::path p = s;
	const auto executableDirectory = p.parent_path();
	const auto folderPath = executableDirectory.generic_wstring();
#elif OSX
	char buff[FILENAME_MAX];
	getcwd( buff, FILENAME_MAX );
	std::string current_working_dir(buff);
	path = wstring(sss + L"\\resources\\");
#elif __linux__
	const auto currentPath = string(get_current_dir_name());
	const fs::path p = currentPath;
	const auto executableDirectory = p.parent_path();
	const auto folderPath = executableDirectory.generic_wstring();
	path = wstring(folderPath + L"/build/snake/resources/");
#endif
    return path;
}

std::shared_ptr<File> FileSystem::LoadFile(std::wstring filename)
{
	const auto directory = GetResourcesDirectory();
	auto file = std::make_shared<File>();
	file->Open(directory + filename);
	return file;
}