#pragma once
#include "filesystem/IFile.h"
#include <windows.h>

namespace Engine
{
    class File : public IFile
    {
        public:
            void Load(std::wstring filename);
            bool IsLoaded() { return mFileHandle != nullptr; }
            FILE * Get() { return mFileHandle; }
        
        private:
            FILE * mFileHandle = nullptr;
    };
}