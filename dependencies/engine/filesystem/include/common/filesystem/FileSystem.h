#pragma once
#include "filesystem/IFileSystem.h"

namespace Engine
{
    class FileSystem final : public IFileSystem
    {
        std::string getResourcesDirectory() override;
        std::shared_ptr<File> loadFile(std::string filename, bool writeable) override;
    };
}