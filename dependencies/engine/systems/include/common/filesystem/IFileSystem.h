#pragma once
#include <string>
#include <memory>

namespace Engine {
    class IFile;

    class IFileSystem {
    public:
        virtual std::wstring GetResourcesDirectory() = 0;
        // virtual std::shared_ptr<IFile> Load(std::wstring filename) = 0;
    };
}