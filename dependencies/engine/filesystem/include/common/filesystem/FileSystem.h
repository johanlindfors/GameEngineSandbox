#pragma once
#include "filesystem/IFileSystem.h"

namespace Engine
{
    class FileSystem : public IFileSystem
    {
        std::wstring GetResourcesDirectory();
        // std::shared_ptr<IFile> Load(std::wstring filename);
    };
}