#pragma once
#include <string>
#include <memory>

namespace Engine
{
    class File 
    {

    };

    class IFileSystem {
    public:
        virtual std::wstring GetResourcesDirectory() = 0;
    };

    class FileSystem : public IFileSystem
    {
        std::wstring GetResourcesDirectory();
        // std::shared_ptr<File> LoadFile();
    };
}