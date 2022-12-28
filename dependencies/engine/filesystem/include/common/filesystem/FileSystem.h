#pragma once
#include "filesystem/IFileSystem.h"

namespace Engine
{
    class FileSystem final : public IFileSystem
    {
        std::string GetResourcesDirectory() override;
        std::shared_ptr<File> LoadFile(std::string filename, bool writeable) override;
    };
}