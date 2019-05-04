#include "filesystem/FileSystem.h"

#ifdef UWP
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.ApplicationModel.h>
using namespace winrt;
using namespace Windows::Storage;
using namespace Windows::ApplicationModel;
#elif WIN32
#include <Windows.h>
#endif

using namespace Engine;

std::wstring FileSystem::GetResourcesDirectory()
{
#ifdef UWP
    auto folder = Package::Current().InstalledLocation();
    std::wstring path(folder.Path() + L"\\resources\\");
    return path;
#elif WIN32
	if (IsDebuggerPresent()) 
	{
#if _DEBUG
		return L"\\Debug\\resources\\";
#else
		return L"\\Release\\resources\\";
#endif
	} 
	else
	{
		return L"\\resources\\";
	}
#endif
}