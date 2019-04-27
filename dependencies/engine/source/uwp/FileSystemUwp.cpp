#include "filesystem/FileSystem.h"
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.ApplicationModel.h>

using namespace winrt;
using namespace Engine;
using namespace Windows::Storage;
using namespace Windows::ApplicationModel;

std::wstring FileSystem::GetResourcesDirectory()
{
    auto folder = Package::Current().InstalledLocation();
    std::wstring path(folder.Path() + L"\\");
    return path;
}