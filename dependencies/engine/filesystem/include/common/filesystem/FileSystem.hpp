#pragma once
#include "filesystem/IFileSystem.hpp"

namespace Engine
{
    class FileSystem final : public IFileSystem
    {
    public:
        std::string getAssetsDirectory() override;
        std::shared_ptr<File> loadFile(std::string filename, bool writeable) override;

    private:
        std::string mAssetsDirectory;
    };
}