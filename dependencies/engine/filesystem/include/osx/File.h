#pragma once
#include "filesystem/IFile.h"

namespace Engine
{
    class File : public IFile
    {
        public:
            void Open(std::wstring filename);
            void Close();
            bool IsOpen() { return mFileHandle != nullptr; }
            FILE * Get() { return mFileHandle; }
            std::string ReadAllText();
        
        private:
            FILE * mFileHandle = nullptr;
    };
}
