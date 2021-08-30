#pragma once
#include <string>

namespace Engine
{
    class IFile {
        public:
	    virtual ~IFile() = default;
	    IFile() = default;
            virtual void Open(std::wstring filename) = 0;
            virtual void Close() = 0;
            virtual bool IsOpen() = 0;
    };
}