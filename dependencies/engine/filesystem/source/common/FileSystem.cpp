#include "filesystem/FileSystem.hpp"
#include "filesystem/File.hpp"
#include "utilities/Logger.hpp"

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
#elif defined(PLATFORM_POSIX)
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;
#elif ANDROID
#include <filesystem>
namespace fs = std::filesystem;
#elif __linux__
#include <filesystem>
namespace fs = std::filesystem;
#endif

using namespace std;
using namespace Engine;

string FileSystem::getAssetsDirectory()
{
	if (mAssetsDirectory.size() == 0)
	{
		debuglog << "Iterating over filesystem..." << endl;
#ifdef UWP
		const auto folder = Package::Current().InstalledLocation();
		const auto folderPath = folder.Path();
		mAssetsDirectory = string(folderPath + L"\\assets\\");
#elif WIN32
		const unsigned int bufferSize = 512;
		vector<char> buffer(bufferSize + 1);
		::GetModuleFileName(nullptr, &buffer[0], bufferSize);
		const string s = &buffer[0];
		const filesystem::path p(s);
		const auto executableDirectory = p.parent_path();
		const auto folderPath = executableDirectory.generic_string();
		mAssetsDirectory = string(folderPath + "/assets/");
#elif defined(PLATFORM_POSIX)
		for (auto const &dir_entry : filesystem::recursive_directory_iterator(filesystem::current_path()))
		{
			if (dir_entry.is_directory() && dir_entry.path().filename() == "assets")
			{
				mAssetsDirectory = string(dir_entry.path().generic_string() + "/");
				break;
			}
		}
#else
		static_assert("Invalid platform configured");
#endif
	}
	debuglog << mAssetsDirectory.c_str() << endl;
    return mAssetsDirectory;
}

std::shared_ptr<File> FileSystem::loadFile(std::string filename, bool writeable)
{
	const auto directory = getAssetsDirectory();
	auto file = std::make_shared<File>();
	file->open(directory + filename, writeable);
	return file;
}