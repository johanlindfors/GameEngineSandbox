#pragma once
#include "filesystem/IFile.h"

namespace Engine
{
    class File : public IFile
    {
        public:
            // Engine::IFile
            void Open(std::string filename, bool writeable) override;
            void Create(std::string filename) override;
            void Close() override;
            bool IsOpen() override { return mFileHandle != nullptr; }
            FILE * Get() const { return mFileHandle; }
            std::string ReadAllText() override;

        private:
            FILE * mFileHandle = nullptr;
            std::string mFilename;
    };
}
