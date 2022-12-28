#pragma once
#include "filesystem/IFile.h"
#include <winrt/Windows.Storage.h>

namespace Engine
{
    class File : public IFile
    {
        public:
            void Open(std::string filename) override;
            void Close() override;
            bool IsOpen() override { return mStorageFile != nullptr; }
            winrt::Windows::Storage::IStorageFile Get() const { return mStorageFile; }
            std::string ReadAllText();

        private:
            winrt::Windows::Storage::IStorageFile mStorageFile = { nullptr };
    };
}