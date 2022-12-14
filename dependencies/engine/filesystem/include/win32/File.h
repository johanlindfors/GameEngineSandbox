#pragma once
#include "filesystem/IFile.h"
#include <windows.h>

namespace Engine
{
    class File : public IFile
    {
        public:
    	// Engine::IFile
            void Open(std::wstring filename) override;
            void Close() override;
            bool IsOpen() override { return mFileHandle != nullptr; }
            FILE * Get() const { return mFileHandle; }
            std::string ReadAllText();
            
        private:
            FILE * mFileHandle = nullptr;
    };
}