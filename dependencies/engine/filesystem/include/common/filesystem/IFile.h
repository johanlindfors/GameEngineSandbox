#pragma once
#include <string>

namespace Engine
{
    class IFile {
        public:
	    virtual ~IFile() = default;
	    IFile() = default;
            virtual void Open(std::string filename) = 0;
            virtual void Close() = 0;
            virtual bool IsOpen() = 0;
            virtual std::string ReadAllText() = 0;
    };
}