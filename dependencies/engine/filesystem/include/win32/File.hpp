#pragma once
#include "filesystem/IFile.hpp"
#include <windows.h>

namespace Engine
{
    class File : public IFile
    {
        public:
    	// Engine::IFile
            void open(std::string filename, bool writeable) override;
            void create(std::string filename) override;
            void close() override;
            bool isOpen() override { return mFileHandle != nullptr; }
            FILE * get() const { return mFileHandle; }
            std::string readAllText();
            
        private:
            FILE * mFileHandle = nullptr;
            std::string mFilename;
    };
}