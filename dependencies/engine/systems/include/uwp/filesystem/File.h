#pragma once
#include "filesystem/IFile.h"
#include <winrt/Windows.Storage.h>

namespace Engine
{
    class File : public IFile
    {
        public:
            void Open(std::wstring filename);
            void Close();
            bool IsOpen() { return mStorageFile != nullptr; }
            winrt::Windows::Storage::IStorageFile Get() { return mStorageFile; }
        
        private:
            winrt::Windows::Storage::IStorageFile mStorageFile = { nullptr };
    };
}