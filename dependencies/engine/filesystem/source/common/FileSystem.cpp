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
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#endif

using namespace Engine;

std::wstring FileSystem::GetResourcesDirectory()
{
#ifdef UWP
	const auto folder = Package::Current().InstalledLocation();
	const auto folderPath = folder.Path();
#elif WIN32
	unsigned int bufferSize = 512;
	std::vector<char> buffer(bufferSize + 1);
	::GetModuleFileName(NULL, &buffer[0], bufferSize);
	std::string s = &buffer[0];
	fs::path p = s;
	auto executableDirectory = p.parent_path();
	auto folderPath = executableDirectory.generic_wstring();
#endif
    std::wstring path(folderPath + L"\\resources\\");
    return path;
}

std::shared_ptr<File> FileSystem::LoadFile(std::wstring filename)
{
	const auto directory = GetResourcesDirectory();
	auto file = std::make_shared<File>();
	file->Open(directory + filename);
	return file;
}