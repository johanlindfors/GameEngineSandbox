#pragma once
#include "filesystem/IFileSystem.h"

namespace Engine
{
    class FileSystem final : public IFileSystem
    {
        std::wstring GetResourcesDirectory() override;
        std::shared_ptr<File> LoadFile(std::wstring filename) override;
    };
}