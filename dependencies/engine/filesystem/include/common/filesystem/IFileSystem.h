#pragma once
#include <string>
#include <memory>

namespace Engine {
    class File;

    class IFileSystem {
    public:
	    virtual ~IFileSystem() = default;
	    virtual std::wstring GetResourcesDirectory() = 0;
        virtual std::shared_ptr<File> LoadFile(std::wstring filename) = 0;
    };
}