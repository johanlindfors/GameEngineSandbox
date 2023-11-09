#pragma once
#include <string>

namespace Engine
{
    class IFile
    {
    public:
        virtual ~IFile() = default;
        IFile() = default;
        virtual void open(std::string filename, bool writeable) = 0;
        virtual void create(std::string filename) = 0;
        virtual void close() = 0;
        virtual bool isOpen() = 0;
        virtual std::string readAllText() = 0;
    };
}