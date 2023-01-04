#pragma once
#include "filesystem/IFile.h"
#include <winrt/Windows.Storage.h>

namespace Engine
{
    class File : public IFile
    {
        public:
            void open(std::string filename) override;
            void close() override;
            bool isOpen() override { return mStorageFile != nullptr; }
            winrt::Windows::Storage::IStorageFile get() const { return mStorageFile; }
            std::string readAllText();

        private:
            winrt::Windows::Storage::IStorageFile mStorageFile = { nullptr };
    };
}