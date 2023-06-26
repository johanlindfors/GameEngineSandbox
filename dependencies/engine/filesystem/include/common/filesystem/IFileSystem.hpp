#pragma once
#include <string>
#include <memory>

namespace Engine {
    class File;

    class IFileSystem {
    public:
	    virtual ~IFileSystem() = default;
	    virtual std::string getAssetsDirectory() = 0;
        virtual std::shared_ptr<File> loadFile(std::string filename, bool writeable) = 0;
    };
}